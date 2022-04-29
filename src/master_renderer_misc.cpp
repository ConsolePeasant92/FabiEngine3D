#include "master_renderer.hpp"

#include <intrin.h>

using std::make_shared;

void MasterRenderer::setBackgroundColor(const fvec3 & color)
{
	glClearColor(color.r, color.g, color.b, 1.0f);
}

/* https://stackoverflow.com/questions/850774/how-to-determine-the-hardware-cpu-and-ram-on-a-machine */
const string MasterRenderer::getCpuName() const
{
	int CPUInfo[4];
	char model[48];

	__cpuid(CPUInfo, 0x80000002);
	memcpy(model, CPUInfo, sizeof(CPUInfo));
	__cpuid(CPUInfo, 0x80000003);
	memcpy(model + 16, CPUInfo, sizeof(CPUInfo));
	__cpuid(CPUInfo, 0x80000004);
	memcpy(model + 32, CPUInfo, sizeof(CPUInfo));

	string nameString;
	for(int index = 0; index < 48; index++)
	{
		nameString.push_back(model[index]);
	}

	string result;
	reverse(nameString.begin(), nameString.end());
	for(int index = 0; index < static_cast<int>(nameString.size()); index++)
	{
		if(nameString[index] != 0)
		{
			result = nameString.substr(index);

			break;
		}
	}

	reverse(result.begin(), result.end());
	return result;
}

const string MasterRenderer::getGpuName() const
{
	return (reinterpret_cast<char *>(const_cast<GLubyte *>(glGetString(GL_RENDERER))));
}

const string MasterRenderer::getOpenglVersion() const
{
	return string(reinterpret_cast<char *>(const_cast<GLubyte *>(glGetString(GL_VERSION)))).substr(0, 3);
}

void MasterRenderer::inject(shared_ptr<Camera> camera)
{
	_camera = camera;

	_skyEntityColorRenderer->inject(_camera);
	_terrainEntityColorRenderer->inject(_camera);
	_terrainEntityDepthRenderer->inject(_camera);
	_waterEntityColorRenderer->inject(_camera);
	_waterEntityDepthRenderer->inject(_camera);
	_modelEntityColorRenderer->inject(_camera);
	_modelEntityDepthRenderer->inject(_camera);
	_modelEntityShadowRenderer->inject(_camera);
	_quad3dEntityColorRenderer->inject(_camera);
	_quad3dEntityDepthRenderer->inject(_camera);
	_quad3dEntityShadowRenderer->inject(_camera);
	_aabbEntityColorRenderer->inject(_camera);
	_aabbEntityDepthRenderer->inject(_camera);
	_quad2dEntityColorRenderer->inject(_camera);
	_antiAliasingRenderer->inject(_camera);
	_bloomRenderer->inject(_camera);
	_dofRenderer->inject(_camera);
	_lensFlareRenderer->inject(_camera);
	_motionBlurRenderer->inject(_camera);
	_bloomBlurRendererHighQuality->inject(_camera);
	_bloomBlurRendererLowQuality->inject(_camera);
	_dofBlurRenderer->inject(_camera);
	_motionBlurBlurRenderer->inject(_camera);
}

void MasterRenderer::inject(shared_ptr<Timer> timer)
{
	_timer = timer;
}

void MasterRenderer::inject(shared_ptr<SkyManager> skyManager)
{
	_skyManager = skyManager;
}

void MasterRenderer::inject(shared_ptr<TerrainManager> terrainManager)
{
	_terrainManager = terrainManager;
}

void MasterRenderer::inject(shared_ptr<WaterManager> waterManager)
{
	_waterManager = waterManager;
}

void MasterRenderer::inject(shared_ptr<ModelManager> modelManager)
{
	_modelManager = modelManager;
}

void MasterRenderer::inject(shared_ptr<Quad3dManager> quad3dManager)
{
	_quad3dManager = quad3dManager;
}

void MasterRenderer::inject(shared_ptr<Text3dManager> text3dManager)
{
	_text3dManager = text3dManager;
}

void MasterRenderer::inject(shared_ptr<AabbManager> aabbManager)
{
	_aabbManager = aabbManager;
}

void MasterRenderer::inject(shared_ptr<Quad2dManager> quad2dManager)
{
	_quad2dManager = quad2dManager;
}

void MasterRenderer::inject(shared_ptr<Text2dManager> text2dManager)
{
	_text2dManager = text2dManager;
}

void MasterRenderer::inject(shared_ptr<PointlightManager> pointlightManager)
{
	_pointlightManager = pointlightManager;
}

void MasterRenderer::inject(shared_ptr<SpotlightManager> spotlightManager)
{
	_spotlightManager = spotlightManager;
}

void MasterRenderer::inject(shared_ptr<CaptorManager> captorManager)
{
	_captorManager = captorManager;
}

void MasterRenderer::inject(shared_ptr<RenderStorage> renderStorage)
{
	_renderStorage = renderStorage;

	_skyEntityColorRenderer->inject(_renderStorage);
	_terrainEntityColorRenderer->inject(_renderStorage);
	_terrainEntityDepthRenderer->inject(_renderStorage);
	_waterEntityColorRenderer->inject(_renderStorage);
	_waterEntityDepthRenderer->inject(_renderStorage);
	_modelEntityColorRenderer->inject(_renderStorage);
	_modelEntityDepthRenderer->inject(_renderStorage);
	_modelEntityShadowRenderer->inject(_renderStorage);
	_quad3dEntityColorRenderer->inject(_renderStorage);
	_quad3dEntityDepthRenderer->inject(_renderStorage);
	_quad3dEntityShadowRenderer->inject(_renderStorage);
	_aabbEntityColorRenderer->inject(_renderStorage);
	_aabbEntityDepthRenderer->inject(_renderStorage);
	_quad2dEntityColorRenderer->inject(_renderStorage);
	_antiAliasingRenderer->inject(_renderStorage);
	_bloomRenderer->inject(_renderStorage);
	_dofRenderer->inject(_renderStorage);
	_lensFlareRenderer->inject(_renderStorage);
	_motionBlurRenderer->inject(_renderStorage);
	_bloomBlurRendererHighQuality->inject(_renderStorage);
	_bloomBlurRendererLowQuality->inject(_renderStorage);
	_dofBlurRenderer->inject(_renderStorage);
	_motionBlurBlurRenderer->inject(_renderStorage);

	reloadBloomBlurQuality();
	reloadDofBlurQuality();
	reloadMotionBlurBlurQuality();
	reloadCubeReflectionQuality();
	reloadPlanarReflectionQuality();
	reloadWaterReflectionQuality();
	reloadWaterRefractionQuality();
	reloadShadowQuality();
}

void MasterRenderer::reloadBloomBlurQuality()
{
	const auto viewportSize = Configuration::getInst().getDisplaySize();

	_bloomBlurHighQualityCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / _renderStorage->getBloomQuality()), 1, true);
	_bloomBlurLowQualityCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / (_renderStorage->getBloomQuality() * 2)), 1, true);

	_bloomBlurRendererHighQuality->inject(_bloomBlurHighQualityCaptureBuffer);
	_bloomBlurRendererLowQuality->inject(_bloomBlurLowQualityCaptureBuffer);
}

void MasterRenderer::reloadDofBlurQuality()
{
	const auto viewportSize = Configuration::getInst().getDisplaySize();

	_dofBlurCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / _renderStorage->getDofQuality()), 1, true);

	_dofBlurRenderer->inject(_dofBlurCaptureBuffer);
}

void MasterRenderer::reloadMotionBlurBlurQuality()
{
	const auto viewportSize = Configuration::getInst().getDisplaySize();

	_motionBlurBlurCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / _renderStorage->getMotionBlurQuality()), 1, true);

	_motionBlurBlurRenderer->inject(_motionBlurBlurCaptureBuffer);
}

void MasterRenderer::reloadCubeReflectionQuality()
{
	_cubeReflectionCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderStorage->getCubeReflectionQuality()), 1, false);
}

void MasterRenderer::reloadPlanarReflectionQuality()
{
	_planarReflectionCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderStorage->getPlanarReflectionQuality()), 1, false);
}

void MasterRenderer::reloadWaterReflectionQuality()
{
	_waterReflectionCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderStorage->getPlanarReflectionQuality()), 1, false);
}

void MasterRenderer::reloadWaterRefractionQuality()
{
	_waterRefractionCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderStorage->getPlanarRefractionQuality()), 1, false);
}

void MasterRenderer::reloadShadowQuality()
{
	_shadowCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderStorage->getShadowQuality()));
}