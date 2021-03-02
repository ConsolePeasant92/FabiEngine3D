#include "render_engine.hpp"
#include "configuration.hpp"
#include "render_bus.hpp"

#include <algorithm>

using std::make_shared;

RenderEngine::RenderEngine(RenderBus& renderBus, Timer& timer, TextureLoader& textureLoader) :
	_renderBus(renderBus),
	_timer(timer),
	_textureLoader(textureLoader),
	_skyEntityRenderer        ("sky_entity_shader.vert",       "sky_entity_shader.frag",       renderBus),
	_terrainEntityRenderer    ("terrain_entity_shader.vert",   "terrain_entity_shader.frag",   renderBus),
	_waterEntityRenderer      ("water_entity_shader.vert",     "water_entity_shader.frag",     renderBus),
	_gameEntityRenderer       ("game_entity_shader.vert",      "game_entity_shader.frag",      renderBus),
	_billboardEntityRenderer  ("billboard_entity_shader.vert", "billboard_entity_shader.frag", renderBus),
	_aabbEntityRenderer       ("aabb_entity_shader.vert",      "aabb_entity_shader.frag",      renderBus),
	_guiEntityRenderer        ("gui_entity_shader.vert",       "gui_entity_shader.frag",       renderBus),
	_blurRenderer             ("blur_shader.vert",             "blur_shader.frag",             renderBus),
	_bloomHdrRenderer         ("bloom_hdr_shader.vert",        "bloom_hdr_shader.frag",        renderBus),
	_shadowRenderer           ("shadow_shader.vert",           "shadow_shader.frag",		   renderBus),
	_depthRenderer            ("depth_shader.vert",            "depth_shader.frag",			   renderBus),
	_postRenderer             ("post_shader.vert",             "post_shader.frag",			   renderBus),
	_finalRenderer            ("final_shader.vert",            "final_shader.frag",			   renderBus)
{
	// Framebuffers
	_screenFramebuffer.createColorTexture(Ivec2(0), Config::getInst().getVpSize(), 1, false);
	_msaaFramebuffer.createMsaaTexture(Ivec2(0), Config::getInst().getVpSize(), 0, 1);
	_aaProcessorFramebuffer.createColorTexture(Ivec2(0), Config::getInst().getVpSize(), 1, false);
	_shadowFramebuffer.createDepthTexture(Ivec2(0), Ivec2(0), 1);
	_sceneRefractionFramebuffer.createColorTexture(Ivec2(0), Ivec2(0), 1, false);
	_sceneReflectionFramebuffer.createColorTexture(Ivec2(0), Ivec2(0), 1, false);
	_bloomHdrFramebuffer.createColorTexture(Ivec2(0), Config::getInst().getVpSize(), 1, false);
	_postProcessingFramebuffer.createColorTexture(Ivec2(0), Config::getInst().getVpSize(), 1, false);
	_sceneDepthFramebuffer.createDepthTexture(Ivec2(0), Config::getInst().getVpSize(), 1);
	_blurRenderer.addFramebuffer(static_cast<int>(BlurType::BLOOM),  true);
	_blurRenderer.addFramebuffer(static_cast<int>(BlurType::DOF),    true);
	_blurRenderer.addFramebuffer(static_cast<int>(BlurType::MOTION), true);

	// Final screen texture
	_finalSurface = make_shared<GuiEntity>("finalSurface");
	_finalSurface->addOglBuffer(new OpenGLBuffer(0.0f, 0.0f, 2.0f, 2.0f, true, false));
	_finalSurface->setMirroredVertically(true);
}

void RenderEngine::renderEngineLogo(shared_ptr<GuiEntity> logo, shared_ptr<TextEntity> text, Ivec2 viewport)
{
	// Prepare
	glViewport(0, 0, viewport.x, viewport.y);
	glClear(GL_COLOR_BUFFER_BIT);

	// Bind
	_guiEntityRenderer.bind();

	// Render logo + text
	_guiEntityRenderer.render(logo);
	if (text != nullptr)
	{
		_guiEntityRenderer.render(text);
	}

	// Unbind
	_guiEntityRenderer.unbind();
}

void RenderEngine::renderScene(EntityBus * entityBus, CameraManager& camera)
{
	// General stuff
	_entityBus = entityBus;

	// Wireframe or non-wireframe rendering
	if (_renderBus.isWireframeRenderingEnabled())
	{
		glViewport(Config::getInst().getVpPos().x, Config::getInst().getVpPos().y, Config::getInst().getVpSize().x, Config::getInst().getVpSize().y);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_renderSkyEntity();
		_renderTerrainEntity();
		_renderWaterEntity();
		_renderGameEntities();
		_renderBillboardEntities();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glViewport(0, 0, Config::getInst().getWindowWidth(), Config::getInst().getWindowHeight());
		_renderGuiEntities();
		_renderTextEntities();
		_renderCustomCursor();
	}
	else
	{
		// Update reflection priorities
		bool waterReflectionsNeeded = (_renderBus.isWaterEffectsEnabled() && _entityBus->getWaterEntity() != nullptr) &&
			_entityBus->getWaterEntity()->isReflective();
		bool sceneReflectionsEnabled = _renderBus.isSceneReflectionsEnabled();
		_renderBus.setSceneReflectionsEnabled(sceneReflectionsEnabled && !waterReflectionsNeeded);

		// Pre-rendering
		_timer.startDeltaPart("reflectionPreRender");
		_captureSceneReflections(camera);
		_timer.stopDeltaPart();
		_timer.startDeltaPart("refractionPreRender");
		_captureSceneRefractions();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("shadowPreRender");
		_captureShadows();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("depthPreRender");
		_captureSceneDepth();
		_timer.stopDeltaPart();

		// Bind screen framebuffer
		if (_renderBus.isMsaaEnabled())
		{
			_msaaFramebuffer.bind();
		}
		else
		{
			_screenFramebuffer.bind();
		}

		// 3D rendering
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_renderBus.setTriangleCountingEnabled(true);
		_timer.startDeltaPart("skyEntityRender");
		_renderSkyEntity();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("terrainEntityRender");
		_renderTerrainEntity();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("waterEntityRender");
		_renderWaterEntity();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("gameEntityRender");
		_renderGameEntities();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("billboardEntityRender");
		_renderBillboardEntities();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("aabbEntityRender");
		_renderAabbEntities();
		_timer.stopDeltaPart();
		_renderBus.setTriangleCountingEnabled(false);

		// Unbind screen framebuffer
		_timer.startDeltaPart("postProcessing");
		if (_renderBus.isMsaaEnabled())
		{
			_msaaFramebuffer.processAAData(&_aaProcessorFramebuffer);
			_msaaFramebuffer.unbind();
			_finalSurface->setTexture(_aaProcessorFramebuffer.getTexture(0));
			_renderBus.setSceneMap(_aaProcessorFramebuffer.getTexture(0));
		}
		else
		{
			_screenFramebuffer.unbind();
			_finalSurface->setTexture(_screenFramebuffer.getTexture(0));
			_renderBus.setSceneMap(_screenFramebuffer.getTexture(0));
		}

		// Postprocessing captures
		_captureBloom();
		_captureDofBlur();
		_captureLensFlare();
		_capturePostProcessing();
		_captureMotionBlur(camera);

		// 2D rendering
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render debug screens
		if (_renderBus.isDebugRenderingEnabled())
		{
			glViewport(Config::getInst().getVpPos().x, Config::getInst().getVpPos().y, Config::getInst().getVpSize().x, Config::getInst().getVpSize().y + 1);
			_renderDebugScreens();
			glViewport(0, 0, Config::getInst().getWindowWidth(), Config::getInst().getWindowHeight());
		}
		else // Render final postprocessed texture
		{
			glViewport(Config::getInst().getVpPos().x, Config::getInst().getVpPos().y, Config::getInst().getVpSize().x, Config::getInst().getVpSize().y +0);
			_renderFinalSceneTexture();
			glViewport(0, 0, Config::getInst().getWindowWidth(), Config::getInst().getWindowHeight());
			
		}
		_timer.stopDeltaPart();

		// Render GUI entities
		_timer.startDeltaPart("guiTextEntityRender");
		_renderBus.setTriangleCountingEnabled(true);
		_renderGuiEntities();

		// Render text entities
		_renderTextEntities();

		// Render custom cursor entity
		_renderCustomCursor();
		_renderBus.setTriangleCountingEnabled(false);
		_timer.stopDeltaPart();

		// Update reflection priorities
		_renderBus.setSceneReflectionsEnabled(sceneReflectionsEnabled);
	}
}

void RenderEngine::loadMsaaFramebuffer(int quality)
{
	_msaaFramebuffer.reset();
	_msaaFramebuffer.createMsaaTexture(Ivec2(0), Config::getInst().getVpSize(), 1, quality);
	_renderBus.setMsaaSampleCount(quality);
}

void RenderEngine::loadShadowFramebuffer(int quality)
{
	_shadowFramebuffer.reset();
	_shadowFramebuffer.createDepthTexture(Ivec2(0), Ivec2(quality), 1);
	_renderBus.setShadowMapSize(quality);
}

void RenderEngine::loadReflectionFramebuffer(int quality)
{
	_sceneReflectionFramebuffer.reset();
	_sceneReflectionFramebuffer.createColorTexture(Ivec2(0), Ivec2(quality), 1, false);
	_renderBus.setSceneReflectionMapSize(quality);
}

void RenderEngine::loadRefractionFramebuffer(int quality)
{
	_sceneRefractionFramebuffer.reset();
	_sceneRefractionFramebuffer.createColorTexture(Ivec2(0), Ivec2(quality), 1, false);
	_renderBus.setSceneRefractionMapSize(quality);
}