#include "render_engine.hpp"
#include "shader_bus.hpp"

// Capturing reflection texture
void RenderEngine::_captureSceneReflections(CameraManager & camera)
{
	bool waterReflectionEnabled = _entityBus->getWaterEntity() != nullptr && _shaderBus.isWaterEffectsEnabled();
	waterReflectionEnabled = waterReflectionEnabled && _entityBus->getWaterEntity()->isReflective();
	bool sceneReflectionEnabled = _shaderBus.isSceneReflectionsEnabled();

	// Check if needed to capture scene
	if (waterReflectionEnabled || sceneReflectionEnabled)
	{
		// Calculate distance between camera and reflection surface
		float cameraDistance;
		if (camera.isLookatEnabled())
		{
			cameraDistance = (camera.getPosition().y - camera.getLookat().y);
		}
		else
		{
			cameraDistance = (camera.getPosition().y - _shaderBus.getSceneReflectionHeight());
		}

		// Start capturing reflection
		glEnable(GL_CLIP_DISTANCE0);
		_sceneReflectionFramebuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Change camera angle
		vec3 cameraPos = camera.getPosition();
		vec3 newCameraPos = vec3(cameraPos.x, cameraPos.y - (cameraDistance * 2.0f), cameraPos.z);
		camera.setPosition(newCameraPos);
		camera.invertPitch();
		camera.updateMatrices();

		// Render scene
		bool shadows = _shaderBus.isShadowsEnabled();
		_shaderBus.setShadowsEnabled(false);
		_renderSkyEntity();
		_renderTerrainEntity();
		_renderGameEntities();
		_shaderBus.setShadowsEnabled(shadows);

		// Revert camera angle
		cameraPos = camera.getPosition();
		newCameraPos = vec3(cameraPos.x, cameraPos.y + (cameraDistance * 2.0f), cameraPos.z);
		camera.setPosition(newCameraPos);
		camera.invertPitch();
		camera.updateMatrices();

		// Stop capturing reflection
		_sceneReflectionFramebuffer.unbind();
		glDisable(GL_CLIP_DISTANCE0);

		// Assign texture
		_shaderBus.setSceneReflectionMap(_sceneReflectionFramebuffer.getTexture(0));
	}
}

// Capturing water refraction texture
void RenderEngine::_captureSceneRefractions()
{
	if (_entityBus->getWaterEntity() != nullptr && _shaderBus.isWaterEffectsEnabled() && _entityBus->getWaterEntity()->isRefractive())
	{
		// Bind
		_sceneRefractionFramebuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render scene
		_renderTerrainEntity();

		// Unbind
		_sceneRefractionFramebuffer.unbind();

		// Assign texture
		_shaderBus.setSceneRefractionMap(_sceneRefractionFramebuffer.getTexture(0));
	}
}

// Capturing shadows
void RenderEngine::_captureShadows()
{
	if (_shaderBus.isShadowsEnabled())
	{
		// Bind
		_shadowFramebuffer.bind();
		glClear(GL_DEPTH_BUFFER_BIT);
		_shadowRenderer.bind();

		// Render game entities
		for (auto & entity : _entityBus->getGameEntities()) { _shadowRenderer.renderGameEntity(entity); }

		// Unbind
		_shadowRenderer.unbind();
		_shadowFramebuffer.unbind();
		_shaderBus.setShadowMap(_shadowFramebuffer.getTexture(0));
	}
}

// Capturing bloom parts
void RenderEngine::_captureBloom()
{
	if (_shaderBus.isBloomEnabled())
	{
		// Process scene texture
		_bloomHdrFramebuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT);
		_bloomHdrRenderer.bind();
		_bloomHdrRenderer.render(&_finalSurface, _shaderBus.getSceneMap());
		_bloomHdrRenderer.unbind();
		_bloomHdrFramebuffer.unbind();
	
		// Blur scene texture
		_blurRenderer.bind();
		_shaderBus.setBloomMap(_blurRenderer.blurTexture(&_finalSurface, _bloomHdrFramebuffer.getTexture(0), BLUR_BLOOM, _shaderBus.getBloomBlurSize(), _shaderBus.getBloomIntensity(), BLUR_DIR_BOTH));
		_blurRenderer.unbind();
	}
}

void RenderEngine::_captureDepth()
{
	if (_shaderBus.isDofEnabled() || _shaderBus.isWaterEffectsEnabled())
	{
		// Bind
		_depthFramebuffer.bind();
		glClear(GL_DEPTH_BUFFER_BIT);
		_depthRenderer.bind();

		// Render terrain entity
		_depthRenderer.renderTerrainEntity(_entityBus->getTerrainEntity());

		// Render game entities
		for (auto & entity : _entityBus->getGameEntities())
		{
			_depthRenderer.renderGameEntity(entity);
		}

		// Render billboard entities
		for (auto & entity : _entityBus->getBillboardEntities())
		{
			_depthRenderer.renderBillboardEntity(entity);
		}

		// Unbind
		_depthRenderer.unbind();
		_depthFramebuffer.unbind();
		_shaderBus.setDepthMap(_depthFramebuffer.getTexture(0));
	}
}

void RenderEngine::_captureDofBlur()
{
	if (_shaderBus.isDofEnabled())
	{
		_blurRenderer.bind();
		_shaderBus.setBlurMap(_blurRenderer.blurTexture(&_finalSurface, _shaderBus.getSceneMap(), BLUR_DOF, 4, 1.0f, BLUR_DIR_BOTH));
		_blurRenderer.unbind();
	}
}

void RenderEngine::_capturePostProcessing()
{	
	// Apply bloom and DOF on scene texture
	_bloomDofAdditionFramebuffer.bind();
	_postRenderer.bind();
	_postRenderer.render(&_finalSurface, _shaderBus.getSceneMap(), _shaderBus.getBloomMap(), _shaderBus.getDepthMap(), _shaderBus.getBlurMap());
	_postRenderer.unbind();
	_bloomDofAdditionFramebuffer.unbind();
	_shaderBus.setBloomedDofSceneMap(_bloomDofAdditionFramebuffer.getTexture(0));
}

void RenderEngine::_captureMotionBlur(CameraManager & camera, ivec2 mousePos)
{
	if (_shaderBus.isMotionBlurEnabled())
	{
		// Declare variables
		static float oldMouseX;
		static float oldMouseY;
		int xDifference = mousePos.x - oldMouseX;
		int yDifference = mousePos.y - oldMouseY;
		int blurType;
		int blurStrength;

		// No negative differences
		xDifference = abs(xDifference);
		yDifference = abs(yDifference);

		// Horizontal blur
		if (xDifference > yDifference)
		{
			blurType = BLUR_DIR_HORIZONTAL;
			blurStrength = xDifference > 10 ? 10 : xDifference;
		}
		else // Vertical blur
		{
			blurType = BLUR_DIR_VERTICAL;
			blurStrength = yDifference > 10 ? 10 : yDifference;
		}

		// Blur the scene
		_blurRenderer.bind();
		_shaderBus.setMotionBlurMap(_blurRenderer.blurTexture(&_finalSurface, _shaderBus.getBloomedDofSceneMap(), BLUR_MOTION, blurStrength, 1.0f, blurType));
		_blurRenderer.unbind();

		// Set for next iteration
		oldMouseX = mousePos.x;
		oldMouseY = mousePos.y;
	}
	else
	{
		_shaderBus.setMotionBlurMap(_shaderBus.getBloomedDofSceneMap());
	}
}