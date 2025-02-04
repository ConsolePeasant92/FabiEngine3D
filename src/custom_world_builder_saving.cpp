#include "custom_world_builder.hpp"
#include "tools.hpp"
#include "logger.hpp"

using std::endl;
using std::ofstream;

void CustomWorldBuilder::saveWorldToFile(const string & fileName)
{
	if(!Tools::isApplicationExported() && _currentProjectId.empty())
	{
		abort();
	}

	const auto isExported = Tools::isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "worlds\\custom\\" + fileName + ".fe3d");

	auto file = ofstream(filePath);

	for(const auto & skyId : _addedSkyIds)
	{
		if(!_fe3d->sky_isExisting(skyId))
		{
			continue;
		}

		const auto editorSkyId = _duplicator->getEditorSkyId(skyId);
		const auto rotation = _fe3d->sky_getRotation(skyId);
		const auto lightness = _fe3d->sky_getLightness(skyId);
		const auto color = _fe3d->sky_getColor(skyId);
		const auto rotationOrder = static_cast<int>(_fe3d->sky_getRotationOrder(skyId));
		const auto isWireframed = _fe3d->sky_isWireframed(skyId);
		const auto wireframeColor = _fe3d->sky_getWireframeColor(skyId);
		const auto isSelected = (skyId == _fe3d->sky_getSelectedId());

		auto cubeMapPaths = _fe3d->sky_getCubeMapPaths(skyId);

		for(auto & cubeMapPath : cubeMapPaths)
		{
			if(!cubeMapPath.empty() && !isExported)
			{
				cubeMapPath = cubeMapPath.substr(("projects\\" + _currentProjectId + "\\").size());
			}

			cubeMapPath = (cubeMapPath.empty()) ? "?" : cubeMapPath;

			replace(cubeMapPath.begin(), cubeMapPath.end(), ' ', '?');
		}

		file
			<< "SKY "
			<< skyId
			<< " "
			<< editorSkyId;

		for(const auto & cubeMapPath : cubeMapPaths)
		{
			file
				<< " "
				<< cubeMapPath;
		}

		file
			<< " "
			<< rotation.x
			<< " "
			<< rotation.y
			<< " "
			<< rotation.z
			<< " "
			<< lightness
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< rotationOrder
			<< " "
			<< isWireframed
			<< " "
			<< wireframeColor.r
			<< " "
			<< wireframeColor.g
			<< " "
			<< wireframeColor.b
			<< " "
			<< isSelected
			<< endl;
	}

	for(const auto & terrainId : _addedTerrainIds)
	{
		if(!_fe3d->terrain_isExisting(terrainId))
		{
			continue;
		}

		const auto editorTerrainId = _duplicator->getEditorTerrainId(terrainId);
		const auto maxHeight = _fe3d->terrain_getMaxHeight(terrainId);
		const auto textureRepeat = _fe3d->terrain_getTextureRepeat(terrainId);
		const auto lightness = _fe3d->terrain_getLightness(terrainId);
		const auto color = _fe3d->terrain_getColor(terrainId);
		const auto specularShininess = _fe3d->terrain_getSpecularShininess(terrainId);
		const auto specularIntensity = _fe3d->terrain_getSpecularIntensity(terrainId);
		const auto redTextureRepeat = _fe3d->terrain_getRedTextureRepeat(terrainId);
		const auto greenTextureRepeat = _fe3d->terrain_getGreenTextureRepeat(terrainId);
		const auto blueTextureRepeat = _fe3d->terrain_getBlueTextureRepeat(terrainId);
		const auto isSpecular = _fe3d->terrain_isSpecular(terrainId);
		const auto isWireframed = _fe3d->terrain_isWireframed(terrainId);
		const auto wireframeColor = _fe3d->terrain_getWireframeColor(terrainId);
		const auto minClipPosition = _fe3d->terrain_getMinClipPosition(terrainId);
		const auto maxClipPosition = _fe3d->terrain_getMaxClipPosition(terrainId);
		const auto isShadowed = _fe3d->terrain_isShadowed(terrainId);
		const auto isSelected = (terrainId == _fe3d->terrain_getSelectedId());

		auto diffuseMapPath = _fe3d->terrain_getDiffuseMapPath(terrainId);
		auto normalMapPath = _fe3d->terrain_getNormalMapPath(terrainId);
		auto blendMapPath = _fe3d->terrain_getBlendMapPath(terrainId);
		auto redDiffuseMapPath = _fe3d->terrain_getRedDiffuseMapPath(terrainId);
		auto greenDiffuseMapPath = _fe3d->terrain_getGreenDiffuseMapPath(terrainId);
		auto blueDiffuseMapPath = _fe3d->terrain_getBlueDiffuseMapPath(terrainId);
		auto redNormalMapPath = _fe3d->terrain_getRedNormalMapPath(terrainId);
		auto greenNormalMapPath = _fe3d->terrain_getGreenNormalMapPath(terrainId);
		auto blueNormalMapPath = _fe3d->terrain_getBlueNormalMapPath(terrainId);

		if(!diffuseMapPath.empty() && !isExported)
		{
			diffuseMapPath = diffuseMapPath.substr(("projects\\" + _currentProjectId + "\\").size());
		}

		if(!normalMapPath.empty() && !isExported)
		{
			normalMapPath = normalMapPath.substr(("projects\\" + _currentProjectId + "\\").size());
		}

		if(!blendMapPath.empty() && !isExported)
		{
			blendMapPath = blendMapPath.substr(("projects\\" + _currentProjectId + "\\").size());
		}

		if(!redDiffuseMapPath.empty() && !isExported)
		{
			redDiffuseMapPath = redDiffuseMapPath.substr(("projects\\" + _currentProjectId + "\\").size());
		}

		if(!greenDiffuseMapPath.empty() && !isExported)
		{
			greenDiffuseMapPath = greenDiffuseMapPath.substr(("projects\\" + _currentProjectId + "\\").size());
		}

		if(!blueDiffuseMapPath.empty() && !isExported)
		{
			blueDiffuseMapPath = blueDiffuseMapPath.substr(("projects\\" + _currentProjectId + "\\").size());
		}

		if(!redNormalMapPath.empty() && !isExported)
		{
			redNormalMapPath = redNormalMapPath.substr(("projects\\" + _currentProjectId + "\\").size());
		}

		if(!greenNormalMapPath.empty() && !isExported)
		{
			greenNormalMapPath = greenNormalMapPath.substr(("projects\\" + _currentProjectId + "\\").size());
		}

		if(!blueNormalMapPath.empty() && !isExported)
		{
			blueNormalMapPath = blueNormalMapPath.substr(("projects\\" + _currentProjectId + "\\").size());
		}

		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
		normalMapPath = (normalMapPath.empty()) ? "?" : normalMapPath;
		blendMapPath = (blendMapPath.empty()) ? "?" : blendMapPath;
		redDiffuseMapPath = (redDiffuseMapPath.empty()) ? "?" : redDiffuseMapPath;
		greenDiffuseMapPath = (greenDiffuseMapPath.empty()) ? "?" : greenDiffuseMapPath;
		blueDiffuseMapPath = (blueDiffuseMapPath.empty()) ? "?" : blueDiffuseMapPath;
		redNormalMapPath = (redNormalMapPath.empty()) ? "?" : redNormalMapPath;
		greenNormalMapPath = (greenNormalMapPath.empty()) ? "?" : greenNormalMapPath;
		blueNormalMapPath = (blueNormalMapPath.empty()) ? "?" : blueNormalMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
		replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');
		replace(blendMapPath.begin(), blendMapPath.end(), ' ', '?');
		replace(redDiffuseMapPath.begin(), redDiffuseMapPath.end(), ' ', '?');
		replace(greenDiffuseMapPath.begin(), greenDiffuseMapPath.end(), ' ', '?');
		replace(blueDiffuseMapPath.begin(), blueDiffuseMapPath.end(), ' ', '?');
		replace(redNormalMapPath.begin(), redNormalMapPath.end(), ' ', '?');
		replace(greenNormalMapPath.begin(), greenNormalMapPath.end(), ' ', '?');
		replace(blueNormalMapPath.begin(), blueNormalMapPath.end(), ' ', '?');

		file
			<< "TERRAIN "
			<< terrainId
			<< " "
			<< editorTerrainId
			<< " "
			<< diffuseMapPath
			<< " "
			<< blendMapPath
			<< " "
			<< redDiffuseMapPath
			<< " "
			<< greenDiffuseMapPath
			<< " "
			<< blueDiffuseMapPath
			<< " "
			<< normalMapPath
			<< " "
			<< redNormalMapPath
			<< " "
			<< greenNormalMapPath
			<< " "
			<< blueNormalMapPath
			<< " "
			<< maxHeight
			<< " "
			<< textureRepeat
			<< " "
			<< lightness
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< redTextureRepeat
			<< " "
			<< greenTextureRepeat
			<< " "
			<< blueTextureRepeat
			<< " "
			<< isSpecular
			<< " "
			<< specularShininess
			<< " "
			<< specularIntensity
			<< " "
			<< isWireframed
			<< " "
			<< wireframeColor.r
			<< " "
			<< wireframeColor.g
			<< " "
			<< wireframeColor.b
			<< " "
			<< minClipPosition.x
			<< " "
			<< minClipPosition.y
			<< " "
			<< minClipPosition.z
			<< " "
			<< maxClipPosition.x
			<< " "
			<< maxClipPosition.y
			<< " "
			<< maxClipPosition.z
			<< " "
			<< isShadowed
			<< " "
			<< isSelected
			<< endl;
	}

	for(const auto & waterId : _addedWaterIds)
	{
		if(!_fe3d->water_isExisting(waterId))
		{
			continue;
		}

		const auto editorWaterId = _duplicator->getEditorWaterId(waterId);
		const auto color = _fe3d->water_getColor(waterId);
		const auto rippleSpeed = _fe3d->water_getRippleSpeed(waterId);
		const auto waveSpeed = _fe3d->water_getWaveSpeed(waterId);
		const auto size = _fe3d->water_getSize(waterId);
		const auto textureRepeat = _fe3d->water_getTextureRepeat(waterId);
		const auto waveHeight = _fe3d->water_getWaveHeight(waterId);
		const auto maxDepth = _fe3d->water_getMaxDepth(waterId);
		const auto isEdged = _fe3d->water_isEdged(waterId);
		const auto specularShininess = _fe3d->water_getSpecularShininess(waterId);
		const auto specularIntensity = _fe3d->water_getSpecularIntensity(waterId);
		const auto isSpecular = _fe3d->water_isSpecular(waterId);
		const auto isReflective = _fe3d->water_isReflective(waterId);
		const auto isRefractive = _fe3d->water_isRefractive(waterId);
		const auto height = _fe3d->water_getHeight(waterId);
		const auto isWireframed = _fe3d->water_isWireframed(waterId);
		const auto wireframeColor = _fe3d->water_getWireframeColor(waterId);
		const auto minClipPosition = _fe3d->water_getMinClipPosition(waterId);
		const auto maxClipPosition = _fe3d->water_getMaxClipPosition(waterId);
		const auto lightness = _fe3d->water_getLightness(waterId);
		const auto distortionSize = _fe3d->water_getDistortionSize(waterId);
		const auto distortionFactor = _fe3d->water_getDistortionFactor(waterId);
		const auto captureOffset = _fe3d->water_getCaptureOffset(waterId);
		const auto isCapturingSky = _fe3d->water_isCapturingSky(waterId);
		const auto isCapturingTerrain = _fe3d->water_isCapturingTerrain(waterId);
		const auto isCapturingModels = _fe3d->water_isCapturingModels(waterId);
		const auto isCapturingQuad3ds = _fe3d->water_isCapturingQuad3ds(waterId);
		const auto isCapturingText3ds = _fe3d->water_isCapturingText3ds(waterId);
		const auto isCapturingAabbs = _fe3d->water_isCapturingAabbs(waterId);
		const auto isSelected = (waterId == _fe3d->water_getSelectedId());

		auto dudvMapPath = _fe3d->water_getDudvMapPath(waterId);
		auto normalMapPath = _fe3d->water_getNormalMapPath(waterId);
		auto heightMapPath = _fe3d->water_getHeightMapPath(waterId);

		if(!dudvMapPath.empty() && !isExported)
		{
			dudvMapPath = dudvMapPath.substr(("projects\\" + _currentProjectId + "\\").size());
		}

		if(!dudvMapPath.empty() && !isExported)
		{
			normalMapPath = normalMapPath.substr(("projects\\" + _currentProjectId + "\\").size());
		}

		if(!heightMapPath.empty() && !isExported)
		{
			heightMapPath = heightMapPath.substr(("projects\\" + _currentProjectId + "\\").size());
		}

		dudvMapPath = (dudvMapPath.empty() ? "?" : dudvMapPath);
		normalMapPath = (normalMapPath.empty() ? "?" : normalMapPath);
		heightMapPath = (heightMapPath.empty() ? "?" : heightMapPath);

		replace(dudvMapPath.begin(), dudvMapPath.end(), ' ', '?');
		replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');
		replace(heightMapPath.begin(), heightMapPath.end(), ' ', '?');

		file
			<< "WATER "
			<< waterId
			<< " "
			<< editorWaterId
			<< " "
			<< dudvMapPath
			<< " "
			<< normalMapPath
			<< " "
			<< heightMapPath
			<< " "
			<< isSpecular
			<< " "
			<< isReflective
			<< " "
			<< isRefractive
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< size
			<< " "
			<< textureRepeat
			<< " "
			<< waveHeight
			<< " "
			<< rippleSpeed.x
			<< " "
			<< rippleSpeed.y
			<< " "
			<< waveSpeed.x
			<< " "
			<< waveSpeed.y
			<< " "
			<< isEdged
			<< " "
			<< specularShininess
			<< " "
			<< specularIntensity
			<< " "
			<< maxDepth
			<< " "
			<< height
			<< " "
			<< isWireframed
			<< " "
			<< wireframeColor.r
			<< " "
			<< wireframeColor.g
			<< " "
			<< wireframeColor.b
			<< " "
			<< minClipPosition.x
			<< " "
			<< minClipPosition.y
			<< " "
			<< minClipPosition.z
			<< " "
			<< maxClipPosition.x
			<< " "
			<< maxClipPosition.y
			<< " "
			<< maxClipPosition.z
			<< " "
			<< lightness
			<< " "
			<< distortionSize
			<< " "
			<< distortionFactor
			<< " "
			<< captureOffset
			<< " "
			<< isCapturingSky
			<< " "
			<< isCapturingTerrain
			<< " "
			<< isCapturingModels
			<< " "
			<< isCapturingQuad3ds
			<< " "
			<< isCapturingText3ds
			<< " "
			<< isCapturingAabbs
			<< " "
			<< isSelected
			<< endl;
	}

	for(const auto & modelId : _addedModelIds)
	{
		if(!_fe3d->model_isExisting(modelId))
		{
			continue;
		}

		const auto editorModelId = _duplicator->getEditorModelId(modelId);
		const auto partIds = _fe3d->model_getPartIds(modelId);
		const auto aabbIds = _fe3d->model_getChildAabbIds(modelId);
		const auto animation3dIds = _fe3d->model_getAnimation3dIds(modelId);
		const auto position = _fe3d->model_getBasePosition(modelId);
		const auto rotation = _fe3d->model_getBaseRotation(modelId);
		const auto rotationOrigin = _fe3d->model_getBaseRotationOrigin(modelId);
		const auto size = _fe3d->model_getBaseSize(modelId);
		const auto levelOfDetailDistance = _fe3d->model_getLevelOfDetailDistance(modelId);
		const auto rotationOrder = static_cast<int>(_fe3d->model_getRotationOrder(modelId));
		const auto isShadowed = _fe3d->model_isShadowed(modelId);
		const auto isReflected = _fe3d->model_isReflected(modelId);
		const auto isRefracted = _fe3d->model_isRefracted(modelId);
		const auto minClipPosition = _fe3d->model_getMinClipPosition(modelId);
		const auto maxClipPosition = _fe3d->model_getMaxClipPosition(modelId);
		const auto isVisible = _fe3d->model_isVisible(modelId);

		auto levelOfDetailId = _fe3d->model_getLevelOfDetailId(modelId);

		levelOfDetailId = (levelOfDetailId.empty()) ? "?" : levelOfDetailId;

		file
			<< "MODEL "
			<< modelId
			<< " "
			<< editorModelId
			<< " "
			<< levelOfDetailId
			<< " "
			<< levelOfDetailDistance
			<< " "
			<< rotationOrder
			<< " "
			<< isShadowed
			<< " "
			<< isReflected
			<< " "
			<< isRefracted
			<< " "
			<< isVisible
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< rotation.x
			<< " "
			<< rotation.y
			<< " "
			<< rotation.z
			<< " "
			<< rotationOrigin.x
			<< " "
			<< rotationOrigin.y
			<< " "
			<< rotationOrigin.z
			<< " "
			<< size.x
			<< " "
			<< size.y
			<< " "
			<< size.z
			<< " "
			<< minClipPosition.x
			<< " "
			<< minClipPosition.y
			<< " "
			<< minClipPosition.z
			<< " "
			<< maxClipPosition.x
			<< " "
			<< maxClipPosition.y
			<< " "
			<< maxClipPosition.z
			<< endl;

		for(auto partId : partIds)
		{
			const auto position = _fe3d->model_getPartPosition(modelId, partId);
			const auto rotation = _fe3d->model_getPartRotation(modelId, partId);
			const auto rotationOrigin = _fe3d->model_getPartRotationOrigin(modelId, partId);
			const auto size = _fe3d->model_getPartSize(modelId, partId);
			const auto isSpecular = _fe3d->model_isSpecular(modelId, partId);
			const auto specularShininess = _fe3d->model_getSpecularShininess(modelId, partId);
			const auto specularIntensity = _fe3d->model_getSpecularIntensity(modelId, partId);
			const auto reflectivity = _fe3d->model_getReflectivity(modelId, partId);
			const auto refractivity = _fe3d->model_getRefractivity(modelId, partId);
			const auto lightness = _fe3d->model_getLightness(modelId, partId);
			const auto color = _fe3d->model_getColor(modelId, partId);
			const auto textureRepeat = _fe3d->model_getTextureRepeat(modelId, partId);
			const auto isReflective = _fe3d->model_isReflective(modelId, partId);
			const auto isRefractive = _fe3d->model_isRefractive(modelId, partId);
			const auto reflectionType = static_cast<int>(_fe3d->model_getReflectionType(modelId, partId));
			const auto refractionType = static_cast<int>(_fe3d->model_getRefractionType(modelId, partId));
			const auto isFaceCulled = _fe3d->model_isFaceCulled(modelId, partId);
			const auto isBright = _fe3d->model_isBright(modelId, partId);
			const auto emissionIntensity = _fe3d->model_getEmissionIntensity(modelId, partId);
			const auto opacity = _fe3d->model_getOpacity(modelId, partId);
			const auto minAlpha = _fe3d->model_getMinAlpha(modelId, partId);
			const auto isWireframed = _fe3d->model_isWireframed(modelId, partId);
			const auto wireframeColor = _fe3d->model_getWireframeColor(modelId, partId);

			auto diffuseMapPath = _fe3d->model_getDiffuseMapPath(modelId, partId);
			auto emissionMapPath = _fe3d->model_getEmissionMapPath(modelId, partId);
			auto specularMapPath = _fe3d->model_getSpecularMapPath(modelId, partId);
			auto reflectionMapPath = _fe3d->model_getReflectionMapPath(modelId, partId);
			auto refractionMapPath = _fe3d->model_getRefractionMapPath(modelId, partId);
			auto normalMapPath = _fe3d->model_getNormalMapPath(modelId, partId);

			if(!diffuseMapPath.empty() && !isExported)
			{
				diffuseMapPath = diffuseMapPath.substr(("projects\\" + _currentProjectId + "\\").size());
			}

			if(!emissionMapPath.empty() && !isExported)
			{
				emissionMapPath = emissionMapPath.substr(("projects\\" + _currentProjectId + "\\").size());
			}

			if(!specularMapPath.empty() && !isExported)
			{
				specularMapPath = specularMapPath.substr(("projects\\" + _currentProjectId + "\\").size());
			}

			if(!reflectionMapPath.empty() && !isExported)
			{
				reflectionMapPath = reflectionMapPath.substr(("projects\\" + _currentProjectId + "\\").size());
			}

			if(!refractionMapPath.empty() && !isExported)
			{
				refractionMapPath = refractionMapPath.substr(("projects\\" + _currentProjectId + "\\").size());
			}

			if(!normalMapPath.empty() && !isExported)
			{
				normalMapPath = normalMapPath.substr(("projects\\" + _currentProjectId + "\\").size());
			}

			partId = (partId.empty()) ? "?" : partId;
			diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
			emissionMapPath = (emissionMapPath.empty()) ? "?" : emissionMapPath;
			specularMapPath = (specularMapPath.empty()) ? "?" : specularMapPath;
			reflectionMapPath = (reflectionMapPath.empty()) ? "?" : reflectionMapPath;
			refractionMapPath = (refractionMapPath.empty()) ? "?" : refractionMapPath;
			normalMapPath = (normalMapPath.empty()) ? "?" : normalMapPath;

			replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
			replace(emissionMapPath.begin(), emissionMapPath.end(), ' ', '?');
			replace(specularMapPath.begin(), specularMapPath.end(), ' ', '?');
			replace(reflectionMapPath.begin(), reflectionMapPath.end(), ' ', '?');
			replace(refractionMapPath.begin(), refractionMapPath.end(), ' ', '?');
			replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');

			file
				<< "MODEL_PART "
				<< modelId
				<< " "
				<< partId
				<< " "
				<< diffuseMapPath
				<< " "
				<< emissionMapPath
				<< " "
				<< specularMapPath
				<< " "
				<< reflectionMapPath
				<< " "
				<< refractionMapPath
				<< " "
				<< normalMapPath
				<< " "
				<< reflectionType
				<< " "
				<< refractionType
				<< " "
				<< isSpecular
				<< " "
				<< isReflective
				<< " "
				<< isRefractive
				<< " "
				<< specularShininess
				<< " "
				<< specularIntensity
				<< " "
				<< reflectivity
				<< " "
				<< refractivity
				<< " "
				<< lightness
				<< " "
				<< color.r
				<< " "
				<< color.g
				<< " "
				<< color.b
				<< " "
				<< textureRepeat
				<< " "
				<< isFaceCulled
				<< " "
				<< isBright
				<< " "
				<< emissionIntensity
				<< " "
				<< opacity
				<< " "
				<< minAlpha
				<< " "
				<< position.x
				<< " "
				<< position.y
				<< " "
				<< position.z
				<< " "
				<< rotation.x
				<< " "
				<< rotation.y
				<< " "
				<< rotation.z
				<< " "
				<< rotationOrigin.x
				<< " "
				<< rotationOrigin.y
				<< " "
				<< rotationOrigin.z
				<< " "
				<< size.x
				<< " "
				<< size.y
				<< " "
				<< size.z
				<< " "
				<< isWireframed
				<< " "
				<< wireframeColor.r
				<< " "
				<< wireframeColor.g
				<< " "
				<< wireframeColor.b
				<< endl;
		}

		for(const auto & aabbId : aabbIds)
		{
			const auto isVisible = _fe3d->aabb_isVisible(aabbId);

			file
				<< "MODEL_AABB "
				<< modelId
				<< " "
				<< aabbId
				<< " "
				<< isVisible
				<< endl;
		}

		for(const auto & animation3dId : animation3dIds)
		{
			const auto isPaused = _fe3d->model_isAnimation3dPaused(modelId, animation3dId);
			const auto isAutoPaused = _fe3d->model_isAnimation3dAutopaused(modelId, animation3dId);
			const auto playCount = _fe3d->model_getAnimation3dPlayCount(modelId, animation3dId);
			const auto frameIndex = _fe3d->model_getAnimation3dFrameIndex(modelId, animation3dId);
			const auto speedMultiplier = _fe3d->model_getAnimation3dSpeedMultiplier(modelId, animation3dId);
			const auto partIds = _fe3d->animation3d_getPartIds(animation3dId);
			const auto partCount = partIds.size();

			file
				<< "MODEL_ANIMATION3D "
				<< modelId
				<< " "
				<< animation3dId
				<< " "
				<< isPaused
				<< " "
				<< isAutoPaused
				<< " "
				<< playCount
				<< " "
				<< frameIndex
				<< " "
				<< speedMultiplier
				<< " "
				<< partCount;

			for(auto partId : partIds)
			{
				const auto totalMovement = _fe3d->model_getAnimation3dTotalMovement(modelId, partId, animation3dId);
				const auto totalRotation = _fe3d->model_getAnimation3dTotalRotation(modelId, partId, animation3dId);
				const auto totalScaling = _fe3d->model_getAnimation3dTotalScaling(modelId, partId, animation3dId);
				const auto totalSpeed = _fe3d->model_getAnimation3dTotalSpeed(modelId, partId, animation3dId);

				partId = (partId.empty()) ? "?" : partId;

				file
					<< " "
					<< partId
					<< " "
					<< totalMovement.x
					<< " "
					<< totalMovement.y
					<< " "
					<< totalMovement.z
					<< " "
					<< totalRotation.x
					<< " "
					<< totalRotation.y
					<< " "
					<< totalRotation.z
					<< " "
					<< totalScaling.x
					<< " "
					<< totalScaling.y
					<< " "
					<< totalScaling.z
					<< " "
					<< totalSpeed.x
					<< " "
					<< totalSpeed.y
					<< " "
					<< totalSpeed.z;
			}

			file << endl;
		}
	}

	for(const auto & quad3dId : _addedQuad3dIds)
	{
		if(!_fe3d->quad3d_isExisting(quad3dId))
		{
			continue;
		}

		const auto editorQuad3dId = _duplicator->getEditorQuad3dId(quad3dId);
		const auto aabbIds = _fe3d->quad3d_getChildAabbIds(quad3dId);
		const auto position = _fe3d->quad3d_getPosition(quad3dId);
		const auto rotation = _fe3d->quad3d_getRotation(quad3dId);
		const auto size = _fe3d->quad3d_getSize(quad3dId);
		const auto color = _fe3d->quad3d_getColor(quad3dId);
		const auto isFacingCameraHorizontally = _fe3d->quad3d_isFacingCameraHorizontally(quad3dId);
		const auto isFacingCameraVertically = _fe3d->quad3d_isFacingCameraVertically(quad3dId);
		const auto isHorizontallyFlipped = _fe3d->quad3d_isHorizontallyFlipped(quad3dId);
		const auto isVerticallyFlipped = _fe3d->quad3d_isVerticallyFlipped(quad3dId);
		const auto isReflected = _fe3d->quad3d_isReflected(quad3dId);
		const auto isRefracted = _fe3d->quad3d_isRefracted(quad3dId);
		const auto isShadowed = _fe3d->quad3d_isShadowed(quad3dId);
		const auto lightness = _fe3d->quad3d_getLightness(quad3dId);
		const auto textureRepeat = _fe3d->quad3d_getTextureRepeat(quad3dId);
		const auto isBright = _fe3d->quad3d_isBright(quad3dId);
		const auto emissionIntensity = _fe3d->quad3d_getEmissionIntensity(quad3dId);
		const auto opacity = _fe3d->quad3d_getOpacity(quad3dId);
		const auto minAlpha = _fe3d->quad3d_getMinAlpha(quad3dId);
		const auto rotationOrder = static_cast<int>(_fe3d->quad3d_getRotationOrder(quad3dId));
		const auto isVisible = _fe3d->quad3d_isVisible(quad3dId);
		const auto isWireframed = _fe3d->quad3d_isWireframed(quad3dId);
		const auto wireframeColor = _fe3d->quad3d_getWireframeColor(quad3dId);
		const auto minClipPosition = _fe3d->quad3d_getMinClipPosition(quad3dId);
		const auto maxClipPosition = _fe3d->quad3d_getMaxClipPosition(quad3dId);
		const auto uvMultiplier = _fe3d->quad3d_getUvMultiplier(quad3dId);
		const auto uvOffset = _fe3d->quad3d_getUvOffset(quad3dId);
		const auto animation2dId = _fe3d->quad3d_getAnimation2dId(quad3dId);

		auto diffuseMapPath = _fe3d->quad3d_getDiffuseMapPath(quad3dId);
		auto emissionMapPath = _fe3d->quad3d_getEmissionMapPath(quad3dId);

		if(!diffuseMapPath.empty() && !isExported)
		{
			diffuseMapPath = diffuseMapPath.substr(("projects\\" + _currentProjectId + "\\").size());
		}

		if(!emissionMapPath.empty() && !isExported)
		{
			emissionMapPath = emissionMapPath.substr(("projects\\" + _currentProjectId + "\\").size());
		}

		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
		emissionMapPath = (emissionMapPath.empty()) ? "?" : emissionMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
		replace(emissionMapPath.begin(), emissionMapPath.end(), ' ', '?');

		file
			<< "QUAD3D "
			<< quad3dId
			<< " "
			<< editorQuad3dId
			<< " "
			<< diffuseMapPath
			<< " "
			<< emissionMapPath
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< rotation.x
			<< " "
			<< rotation.y
			<< " "
			<< rotation.z
			<< " "
			<< size.x
			<< " "
			<< size.y
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< isFacingCameraHorizontally
			<< " "
			<< isFacingCameraVertically
			<< " "
			<< isHorizontallyFlipped
			<< " "
			<< isVerticallyFlipped
			<< " "
			<< isReflected
			<< " "
			<< isRefracted
			<< " "
			<< isShadowed
			<< " "
			<< lightness
			<< " "
			<< textureRepeat
			<< " "
			<< isBright
			<< " "
			<< emissionIntensity
			<< " "
			<< opacity
			<< " "
			<< minAlpha
			<< " "
			<< rotationOrder
			<< " "
			<< isVisible
			<< " "
			<< isWireframed
			<< " "
			<< wireframeColor.r
			<< " "
			<< wireframeColor.g
			<< " "
			<< wireframeColor.b
			<< " "
			<< uvMultiplier.x
			<< " "
			<< uvMultiplier.y
			<< " "
			<< uvOffset.x
			<< " "
			<< uvOffset.y
			<< " "
			<< minClipPosition.x
			<< " "
			<< minClipPosition.y
			<< " "
			<< minClipPosition.z
			<< " "
			<< maxClipPosition.x
			<< " "
			<< maxClipPosition.y
			<< " "
			<< maxClipPosition.z
			<< endl;

		for(const auto & aabbId : aabbIds)
		{
			const auto isVisible = _fe3d->aabb_isVisible(aabbId);

			file
				<< "QUAD3D_AABB "
				<< quad3dId
				<< " "
				<< aabbId
				<< " "
				<< isVisible
				<< endl;
		}

		if(!animation2dId.empty())
		{
			const auto isPaused = _fe3d->quad3d_isAnimation2dPaused(quad3dId, animation2dId);
			const auto isAutoPaused = _fe3d->quad3d_isAnimation2dAutopaused(quad3dId, animation2dId);
			const auto playCount = _fe3d->quad3d_getAnimation2dPlayCount(quad3dId, animation2dId);
			const auto rowIndex = _fe3d->quad3d_getAnimation2dRowIndex(quad3dId, animation2dId);
			const auto columnIndex = _fe3d->quad3d_getAnimation2dColumnIndex(quad3dId, animation2dId);
			const auto intervalMultiplier = _fe3d->quad3d_getAnimation2dIntervalMultiplier(quad3dId, animation2dId);
			const auto intervalDivider = _fe3d->quad3d_getAnimation2dIntervalDivider(quad3dId, animation2dId);
			const auto updateCount = _fe3d->quad3d_getAnimation2dUpdateCount(quad3dId, animation2dId);

			file
				<< "QUAD3D_ANIMATION2D "
				<< quad3dId
				<< " "
				<< animation2dId
				<< " "
				<< isPaused
				<< " "
				<< isAutoPaused
				<< " "
				<< playCount
				<< " "
				<< rowIndex
				<< " "
				<< columnIndex
				<< " "
				<< intervalMultiplier
				<< " "
				<< intervalDivider
				<< " "
				<< updateCount
				<< endl;
		}
	}

	for(const auto & text3dId : _addedText3dIds)
	{
		if(!_fe3d->text3d_isExisting(text3dId))
		{
			continue;
		}

		const auto editorText3dId = _duplicator->getEditorText3dId(text3dId);
		const auto aabbIds = _fe3d->text3d_getChildAabbIds(text3dId);
		const auto position = _fe3d->text3d_getPosition(text3dId);
		const auto rotation = _fe3d->text3d_getRotation(text3dId);
		const auto size = _fe3d->text3d_getSize(text3dId);
		const auto color = _fe3d->text3d_getColor(text3dId);
		const auto isFacingCameraHorizontally = _fe3d->text3d_isFacingCameraHorizontally(text3dId);
		const auto isFacingCameraVertically = _fe3d->text3d_isFacingCameraVertically(text3dId);
		const auto isHorizontallyFlipped = _fe3d->text3d_isHorizontallyFlipped(text3dId);
		const auto isVerticallyFlipped = _fe3d->text3d_isVerticallyFlipped(text3dId);
		const auto isReflected = _fe3d->text3d_isReflected(text3dId);
		const auto isRefracted = _fe3d->text3d_isRefracted(text3dId);
		const auto isShadowed = _fe3d->text3d_isShadowed(text3dId);
		const auto lightness = _fe3d->text3d_getLightness(text3dId);
		const auto isBright = _fe3d->text3d_isBright(text3dId);
		const auto opacity = _fe3d->text3d_getOpacity(text3dId);
		const auto minAlpha = _fe3d->text3d_getMinAlpha(text3dId);
		const auto rotationOrder = static_cast<int>(_fe3d->text3d_getRotationOrder(text3dId));
		const auto isVisible = _fe3d->text3d_isVisible(text3dId);
		const auto isWireframed = _fe3d->text3d_isWireframed(text3dId);
		const auto wireframeColor = _fe3d->text3d_getWireframeColor(text3dId);
		const auto minClipPosition = _fe3d->text3d_getMinClipPosition(text3dId);
		const auto maxClipPosition = _fe3d->text3d_getMaxClipPosition(text3dId);
		const auto content = _fe3d->text3d_getContent(text3dId);

		file
			<< "TEXT3D "
			<< text3dId
			<< " "
			<< editorText3dId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< rotation.x
			<< " "
			<< rotation.y
			<< " "
			<< rotation.z
			<< " "
			<< size.x
			<< " "
			<< size.y
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< isFacingCameraHorizontally
			<< " "
			<< isFacingCameraVertically
			<< " "
			<< isHorizontallyFlipped
			<< " "
			<< isVerticallyFlipped
			<< " "
			<< isReflected
			<< " "
			<< isRefracted
			<< " "
			<< isShadowed
			<< " "
			<< lightness
			<< " "
			<< isBright
			<< " "
			<< opacity
			<< " "
			<< minAlpha
			<< " "
			<< rotationOrder
			<< " "
			<< isVisible
			<< " "
			<< isWireframed
			<< " "
			<< wireframeColor.r
			<< " "
			<< wireframeColor.g
			<< " "
			<< wireframeColor.b
			<< " "
			<< minClipPosition.x
			<< " "
			<< minClipPosition.y
			<< " "
			<< minClipPosition.z
			<< " "
			<< maxClipPosition.x
			<< " "
			<< maxClipPosition.y
			<< " "
			<< maxClipPosition.z
			<< " "
			<< content
			<< endl;

		for(const auto & aabbId : aabbIds)
		{
			const auto isVisible = _fe3d->aabb_isVisible(aabbId);

			file
				<< "TEXT3D_AABB "
				<< text3dId
				<< " "
				<< aabbId
				<< " "
				<< isVisible
				<< endl;
		}
	}

	for(const auto & aabbId : _addedAabbIds)
	{
		if(!_fe3d->aabb_isExisting(aabbId))
		{
			continue;
		}

		const auto editorAabbId = _duplicator->getEditorAabbId(aabbId);
		const auto position = _fe3d->aabb_getBasePosition(aabbId);
		const auto size = _fe3d->aabb_getBaseSize(aabbId);
		const auto color = _fe3d->aabb_getColor(aabbId);
		const auto isRaycastResponsive = _fe3d->aabb_isRaycastResponsive(aabbId);
		const auto isCollisionResponsive = _fe3d->aabb_isCollisionResponsive(aabbId);
		const auto isVisible = _fe3d->aabb_isVisible(aabbId);
		const auto minClipPosition = _fe3d->aabb_getMinClipPosition(aabbId);
		const auto maxClipPosition = _fe3d->aabb_getMaxClipPosition(aabbId);

		file
			<< "AABB "
			<< aabbId
			<< " "
			<< editorAabbId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< size.x
			<< " "
			<< size.y
			<< " "
			<< size.z
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< isRaycastResponsive
			<< " "
			<< isCollisionResponsive
			<< " "
			<< isVisible
			<< " "
			<< minClipPosition.x
			<< " "
			<< minClipPosition.y
			<< " "
			<< minClipPosition.z
			<< " "
			<< maxClipPosition.x
			<< " "
			<< maxClipPosition.y
			<< " "
			<< maxClipPosition.z
			<< endl;
	}

	for(const auto & pointlightId : _addedPointlightIds)
	{
		if(!_fe3d->pointlight_isExisting(pointlightId))
		{
			continue;
		}

		const auto editorPointlightId = _duplicator->getEditorPointlightId(pointlightId);
		const auto position = _fe3d->pointlight_getPosition(pointlightId);
		const auto radius = _fe3d->pointlight_getRadius(pointlightId);
		const auto color = _fe3d->pointlight_getColor(pointlightId);
		const auto intensity = _fe3d->pointlight_getIntensity(pointlightId);
		const auto shape = static_cast<int>(_fe3d->pointlight_getShape(pointlightId));
		const auto isVisible = _fe3d->pointlight_isVisible(pointlightId);

		file
			<< "POINTLIGHT "
			<< pointlightId
			<< " "
			<< editorPointlightId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< radius.x
			<< " "
			<< radius.y
			<< " "
			<< radius.z
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< intensity
			<< " "
			<< shape
			<< " "
			<< isVisible
			<< endl;
	}

	for(const auto & spotlightId : _addedSpotlightIds)
	{
		if(!_fe3d->spotlight_isExisting(spotlightId))
		{
			continue;
		}

		const auto editorSpotlightId = _duplicator->getEditorSpotlightId(spotlightId);
		const auto position = _fe3d->spotlight_getPosition(spotlightId);
		const auto yaw = _fe3d->spotlight_getYaw(spotlightId);
		const auto pitch = _fe3d->spotlight_getPitch(spotlightId);
		const auto color = _fe3d->spotlight_getColor(spotlightId);
		const auto intensity = _fe3d->spotlight_getIntensity(spotlightId);
		const auto angle = _fe3d->spotlight_getAngle(spotlightId);
		const auto distance = _fe3d->spotlight_getDistance(spotlightId);
		const auto isVisible = _fe3d->spotlight_isVisible(spotlightId);

		file
			<< "SPOTLIGHT "
			<< spotlightId
			<< " "
			<< editorSpotlightId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< yaw
			<< " "
			<< pitch
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< intensity
			<< " "
			<< angle
			<< " "
			<< distance
			<< " "
			<< isVisible
			<< endl;
	}

	for(const auto & captorId : _addedCaptorIds)
	{
		if(!_fe3d->captor_isExisting(captorId))
		{
			continue;
		}

		const auto editorCaptorId = _duplicator->getEditorCaptorId(captorId);
		const auto position = _fe3d->captor_getPosition(captorId);

		auto exceptionId = _fe3d->captor_getExceptionId(captorId);

		exceptionId = (exceptionId.empty()) ? "?" : exceptionId;

		file
			<< "CAPTOR "
			<< captorId
			<< " "
			<< editorCaptorId
			<< " "
			<< exceptionId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< endl;
	}

	for(const auto & sound3dId : _addedSound3dIds)
	{
		if(!_fe3d->sound3d_isExisting(sound3dId))
		{
			continue;
		}

		const auto editorSound3dId = _duplicator->getEditorSound3dId(sound3dId);
		const auto position = _fe3d->sound3d_getPosition(sound3dId);
		const auto maxVolume = _fe3d->sound3d_getMaxVolume(sound3dId);
		const auto maxDistance = _fe3d->sound3d_getMaxDistance(sound3dId);
		const auto startedCount = _fe3d->sound3d_getStartedCount(sound3dId);

		file
			<< "SOUND3D "
			<< sound3dId
			<< " "
			<< editorSound3dId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< maxVolume
			<< " "
			<< maxDistance
			<< " "
			<< startedCount;

		for(int index = 0; index < startedCount; index++)
		{
			const auto isStarted = _fe3d->sound3d_isStarted(sound3dId, index);
			const auto isPaused = (isStarted ? _fe3d->sound3d_isPaused(sound3dId, index) : false);
			const auto playCount = (isStarted ? _fe3d->sound3d_getPlayCount(sound3dId, index) : false);
			const auto currentTime = (isStarted ? _fe3d->sound3d_getCurrentTime(sound3dId, index) : 0.0f);

			file
				<< " "
				<< isStarted
				<< " "
				<< isPaused
				<< " "
				<< playCount
				<< " "
				<< currentTime;
		}

		file << endl;
	}

	if(_fe3d->graphics_isAmbientLightingEnabled())
	{
		const auto ambientLightingColor = _fe3d->graphics_getAmbientLightingColor();
		const auto ambientLightingIntensity = _fe3d->graphics_getAmbientLightingIntensity();

		file
			<< "GRAPHICS_AMBIENT_LIGHTING "
			<< ambientLightingColor.r
			<< " "
			<< ambientLightingColor.g
			<< " "
			<< ambientLightingColor.b
			<< " "
			<< ambientLightingIntensity
			<< endl;
	}

	if(_fe3d->graphics_isDirectionalLightingEnabled())
	{
		const auto directionalLightingColor = _fe3d->graphics_getDirectionalLightingColor();
		const auto directionalLightingPosition = _fe3d->graphics_getDirectionalLightingPosition();
		const auto directionalLightingIntensity = _fe3d->graphics_getDirectionalLightingIntensity();

		file
			<< "GRAPHICS_DIRECTIONAL_LIGHTING "
			<< directionalLightingPosition.x
			<< " "
			<< directionalLightingPosition.y
			<< " "
			<< directionalLightingPosition.z
			<< " "
			<< directionalLightingColor.r
			<< " "
			<< directionalLightingColor.g
			<< " "
			<< directionalLightingColor.b
			<< " "
			<< directionalLightingIntensity
			<< endl;
	}

	if(_fe3d->graphics_isShadowsEnabled())
	{
		const auto size = _fe3d->graphics_getShadowSize();
		const auto lightness = _fe3d->graphics_getShadowLightness();
		const auto position = _fe3d->graphics_getShadowPositionOffset();
		const auto lookat = _fe3d->graphics_getShadowLookatOffset();
		const auto isFollowingCameraX = _fe3d->graphics_isShadowFollowingCameraX();
		const auto isFollowingCameraY = _fe3d->graphics_isShadowFollowingCameraY();
		const auto isFollowingCameraZ = _fe3d->graphics_isShadowFollowingCameraZ();
		const auto interval = _fe3d->graphics_getShadowInterval();
		const auto pcfCount = _fe3d->graphics_getShadowPcfCount();
		const auto quality = _fe3d->graphics_getShadowQuality();
		const auto bias = _fe3d->graphics_getShadowBias();

		file
			<< "GRAPHICS_SHADOWS "
			<< size
			<< " "
			<< lightness
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< lookat.x
			<< " "
			<< lookat.y
			<< " "
			<< lookat.z
			<< " "
			<< isFollowingCameraX
			<< " "
			<< isFollowingCameraY
			<< " "
			<< isFollowingCameraZ
			<< " "
			<< interval
			<< " "
			<< pcfCount
			<< " "
			<< quality
			<< " "
			<< bias
			<< endl;
	}

	{
		const auto height = _fe3d->graphics_getPlanarReflectionHeight();
		const auto quality = _fe3d->graphics_getPlanarReflectionQuality();

		file
			<< "GRAPHICS_PLANAR_REFLECTIONS "
			<< height
			<< " "
			<< quality
			<< endl;
	}

	{
		const auto height = _fe3d->graphics_getPlanarRefractionHeight();
		const auto quality = _fe3d->graphics_getPlanarReflectionQuality();

		file
			<< "GRAPHICS_PLANAR_REFRACTIONS "
			<< height
			<< " "
			<< quality
			<< endl;
	}

	if(_fe3d->graphics_isDofEnabled())
	{
		const auto dynamic = _fe3d->graphics_isDofDynamic();
		const auto blurDistance = _fe3d->graphics_getDofBlurDistance();
		const auto maxDistance = _fe3d->graphics_getDofDynamicDistance();
		const auto quality = _fe3d->graphics_getDofQuality();

		file
			<< "GRAPHICS_DOF "
			<< dynamic
			<< " "
			<< blurDistance
			<< " "
			<< maxDistance
			<< " "
			<< quality
			<< endl;
	}

	if(_fe3d->graphics_isFogEnabled())
	{
		const auto minDistance = _fe3d->graphics_getFogMinDistance();
		const auto maxDistance = _fe3d->graphics_getFogMaxDistance();
		const auto thickness = _fe3d->graphics_getFogThickness();
		const auto color = _fe3d->graphics_getFogColor();

		file
			<< "GRAPHICS_FOG "
			<< minDistance
			<< " "
			<< maxDistance
			<< " "
			<< thickness
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< endl;
	}

	if(_fe3d->graphics_isLensFlareEnabled())
	{
		const auto intensity = _fe3d->graphics_getLensFlareIntensity();
		const auto sensitivity = _fe3d->graphics_getLensFlareSensitivity();

		auto flareMapPath = _fe3d->graphics_getLensFlareMapPath();

		if(!flareMapPath.empty() && !isExported)
		{
			flareMapPath = flareMapPath.substr(("projects\\" + _currentProjectId + "\\").size());
		}

		flareMapPath = (flareMapPath.empty()) ? "?" : flareMapPath;

		replace(flareMapPath.begin(), flareMapPath.end(), ' ', '?');

		file
			<< "GRAPHICS_LENS_FLARE "
			<< flareMapPath
			<< " "
			<< intensity
			<< " "
			<< sensitivity
			<< endl;
	}

	if(_fe3d->graphics_isSkyExposureEnabled())
	{
		const auto intensity = _fe3d->graphics_getSkyExposureIntensity();
		const auto speed = _fe3d->graphics_getSkyExposureSpeed();

		file
			<< "GRAPHICS_SKY_EXPOSURE "
			<< intensity
			<< " "
			<< speed
			<< endl;
	}

	if(_fe3d->graphics_isBloomEnabled())
	{
		const auto type = static_cast<int>(_fe3d->graphics_getBloomType());
		const auto intensity = _fe3d->graphics_getBloomIntensity();
		const auto blurCount = _fe3d->graphics_getBloomBlurCount();
		const auto quality = _fe3d->graphics_getBloomQuality();

		file
			<< "GRAPHICS_BLOOM "
			<< type
			<< " "
			<< intensity
			<< " "
			<< blurCount
			<< " "
			<< quality
			<< endl;
	}

	file.close();

	Logger::throwInfo("Custom world data saved");
}