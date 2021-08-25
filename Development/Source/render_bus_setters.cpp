#include "render_bus.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void RenderBus::setPlanarReflectionMap(TextureID value)
{
	_planarReflectionMap = value;
}

void RenderBus::setWaterReflectionMap(TextureID value)
{
	_waterReflectionMap = value;
}

void RenderBus::setWaterRefractionMap(TextureID value)
{
	_waterRefractionMap = value;
}

void RenderBus::setBloomMap(TextureID value)
{
	_bloomMap = value;
}

void RenderBus::setPrimarySceneMap(TextureID value)
{
	_primarySceneMap = value;
}

void RenderBus::setSecondarySceneMap(TextureID value)
{
	_secondarySceneMap = value;
}

void RenderBus::setShadowMap(TextureID value)
{
	_shadowMap = value;
}

void RenderBus::setMotionBlurMap(TextureID value)
{
	_motionBlurMap = value;
}

void RenderBus::setLensFlareMap(TextureID value)
{
	_lensFlareMap = value;
}

void RenderBus::setDepthMap(TextureID value)
{
	_depthMap = value;
}

void RenderBus::setDofMap(TextureID value)
{
	_dofMap = value;
}

void RenderBus::setFinalSceneMap(TextureID value)
{
	_finalSceneMap = value;
}

void RenderBus::setViewMatrix(const Matrix44 value)
{
	_viewMatrix = value;
}

void RenderBus::setProjectionMatrix(const Matrix44 value)
{
	_projectionMatrix = value;
}

void RenderBus::setShadowMatrix(const Matrix44 value)
{
	_shadowMatrix = value;
}

void RenderBus::setFlareSourcePositionClipspace(Vec4 value)
{
	_flareSourcePositionClipspace = value;
}

void RenderBus::setClippingPlane(Vec4 value)
{
	_clippingPlane = value;
}

void RenderBus::setCameraPosition(Vec3 value)
{
	_cameraPosition = value;
}

void RenderBus::setCameraFront(Vec3 value)
{
	_cameraFront = value;
}

void RenderBus::setAmbientLightingColor(Vec3 value)
{
	_ambientLightColor = Vec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void RenderBus::setDirectionalLightingPosition(Vec3 value)
{
	_directionalLightPosition = value;
}

void RenderBus::setDirectionalLightingColor(Vec3 value)
{
	_directionalLightColor = Vec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void RenderBus::setSpotLightingColor(Vec3 value)
{
	_spotLightColor = Vec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void RenderBus::setShadowEyePosition(Vec3 value)
{
	_shadowEyePosition = value;
}

void RenderBus::setShadowAreaCenter(Vec3 value)
{
	_shadowAreaCenter = value;
}

void RenderBus::setFogColor(Vec3 value)
{
	_fogColor = Vec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void RenderBus::setFlareSourcePosition(Vec3 value)
{
	_flareSourcePosition = value;
}

void RenderBus::setPlanarReflectionHeight(float value)
{
	_planarReflectionHeight = value;
}

void RenderBus::setShadowAreaSize(float value)
{
	_shadowAreaSize = max(0.0f, value);
}

void RenderBus::setShadowAreaReach(float value)
{
	_shadowAreaReach = max(0.0f, value);
}

void RenderBus::setShadowLightness(float value)
{
	_shadowLightness = max(0.0f, value);
}

void RenderBus::setLensFlareAlpha(float value)
{
	_lensFlareAlpha = max(0.0f, value);
}

void RenderBus::setLensFlareIntensity(float value)
{
	_lensFlareIntensity = max(0.0f, value);
}

void RenderBus::setLensFlareMultiplier(float value)
{
	_lensFlareMultiplier = max(0.0f, value);
}

void RenderBus::setMotionBlurStrength(float value)
{
	_motionBlurStrength = max(0.0f, value);
}

void RenderBus::setMotionBlurMixValue(float value)
{
	_motionBlurMixValue = clamp(value, 0.0f, 1.0f);
}

void RenderBus::setSkyMixValue(float value)
{
	_skyMixValue = value;
}

void RenderBus::setMaxSpotLightingAngle(float value)
{
	_maxSpotLightAngle = fmodf(value, 360.0f);
}

void RenderBus::setMaxSpotLightingDistance(float value)
{
	_maxSpotLightDistance = max(0.0f, value);
}

void RenderBus::setAmbientLightingIntensity(float value)
{
	_ambientLightIntensity = max(0.0f, value);
}

void RenderBus::setDirectionalLightingIntensity(float value)
{
	_directionalLightIntensity = max(0.0f, value);
}

void RenderBus::setSpotLightingIntensity(float value)
{
	_spotLightIntensity = max(0.0f, value);
}

void RenderBus::setFogMinDistance(float value)
{
	_fogMinDistance = max(0.0f, value);
}

void RenderBus::setFogMaxDistance(float value)
{
	_fogMaxDistance = max(0.0f, value);
}

void RenderBus::setFogThickness(float value)
{
	_fogThickness = clamp(value, 0.0f, 1.0f);
}

void RenderBus::setBloomIntensity(float value)
{
	_bloomIntensity = max(0.0f, value);
}

void RenderBus::setCameraYaw(float value)
{
	_cameraYaw = value;
}

void RenderBus::setCameraPitch(float value)
{
	_cameraPitch = value;
}

void RenderBus::setNearZ(float value)
{
	_nearZ = max(0.0f, value);
}

void RenderBus::setFarZ(float value)
{
	_farZ = value;
}

void RenderBus::setDofMaxDistance(float value)
{
	_dofMaxDistance = max(0.0f, value);
}

void RenderBus::setDofBlurDistance(float value)
{
	_dofBlurDistance = max(0.0f, value);
}

void RenderBus::setBloomBlurCount(unsigned int value)
{
	_bloomBlurCount = value;
}

void RenderBus::setAnisotropicFilteringQuality(unsigned int value)
{
	_anisotropicFilteringQuality = value;
}

void RenderBus::increaseTriangleCount(unsigned int value)
{
	if (_isTriangleCountingEnabled)
	{
		_triangleCount += value;
	}
}

void RenderBus::setShadowQuality(unsigned int value)
{
	_shadowQuality = value;
}

void RenderBus::setReflectionQuality(unsigned int value)
{
	_reflectionQuality = value;
}

void RenderBus::setRefractionQuality(unsigned int value)
{
	_refractionQuality = value;
}

void RenderBus::resetTriangleCount()
{
	_triangleCount = 0;
}

void RenderBus::setFxaaEnabled(bool value)
{
	_isFxaaEnabled = value;
}

void RenderBus::setAmbientLightingEnabled(bool value)
{
	_isAmbientLightingEnabled = value;
}

void RenderBus::setDirectionalLightingEnabled(bool value)
{
	_isDirectionalLightingEnabled = value;
}

void RenderBus::setSpotLightingEnabled(bool value)
{
	_isSpotLightingEnabled = value;
}

void RenderBus::setReflectionsEnabled(bool value)
{
	_isReflectionsEnabled = value;
}

void RenderBus::setFogEnabled(bool value)
{
	_isFogEnabled = value;
}

void RenderBus::setBloomEnabled(bool value)
{
	_isBloomEnabled = value;
}

void RenderBus::setSkyExposureEnabled(bool value)
{
	_isSkyExposureEnabled = value;
}

void RenderBus::setShadowsEnabled(bool value)
{
	_isShadowsEnabled = value;
}

void RenderBus::setDofEnabled(bool value)
{
	_isDofEnabled = value;
}

void RenderBus::setMotionBlurEnabled(bool value)
{
	_isMotionBlurEnabled = value;
}

void RenderBus::setLensFlareEnabled(bool value)
{
	_isLensFlareEnabled = value;
}

void RenderBus::setWireFrameRenderingEnabled(bool value)
{
	_isWireFrameRenderingEnabled = value;
}

void RenderBus::setAabbFrameRenderingEnabled(bool value)
{
	_isAabbFrameRenderingEnabled = value;
}

void RenderBus::setDebugRenderingEnabled(bool value)
{
	_isDebugRenderingEnabled = value;
}

void RenderBus::setShadowFrameRenderingEnabled(bool value)
{
	_isShadowFrameRenderingEnabled = value;
}

void RenderBus::setTriangleCountingEnabled(bool value)
{
	_isTriangleCountingEnabled = value;
}

void RenderBus::setDofDynamic(bool value)
{
	_isDofDynamic = value;
}

void RenderBus::setBloomType(BloomType value)
{
	_bloomType = value;
}

void RenderBus::setCursorEntityID(const string& value)
{
	_cursorEntityID = value;
}

void RenderBus::setLensFlareMapPath(const string& value)
{
	_lensFlareMapPath = value;
}