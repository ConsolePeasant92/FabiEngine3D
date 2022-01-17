#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;

const bool WorldEditor::saveCustomWorldToFile()
{
	//if(_currentProjectID.empty())
	//{
	//	Logger::throwError("WorldEditor::saveCustomWorldToFile::1");
	//}
	//if(_isEditorLoaded)
	//{
	//	Logger::throwError("WorldEditor::saveCustomWorldToFile::2");
	//}

	//if(_customWorldID.empty())
	//{
	//	Logger::throwWarning("Cannot save custom world!");
	//	return false;
	//}

	//const auto rootPath = Tools::getRootDirectoryPath();
	//const auto filePath = (rootPath + (Config::getInst().isApplicationExported() ? "" :
	//					   ("projects\\" + _currentProjectID + "\\")) + "worlds\\custom\\" + _customWorldID + ".fe3d");

	//ofstream file(filePath);

	//vector<string> levelOfDetailEntityIDs;
	//for(const auto& modelID : _fe3d->model_getIDs())
	//{
	//	bool isCustomWorldModel = find(_customWorldModelIDs.begin(), _customWorldModelIDs.end(), modelID) != _customWorldModelIDs.end();
	//	if((modelID[0] != '@') && isCustomWorldModel)
	//	{
	//		if(!_fe3d->model_getLevelOfDetailEntityID(modelID).empty())
	//		{
	//			if(find(levelOfDetailEntityIDs.begin(), levelOfDetailEntityIDs.end(), modelID) == levelOfDetailEntityIDs.end())
	//			{
	//				levelOfDetailEntityIDs.push_back(_fe3d->model_getLevelOfDetailEntityID(modelID));
	//			}
	//		}
	//	}
	//}

	//string skyID = _fe3d->sky_getSelectedID();
	//if(!skyID.empty() && _hasCustomWorldSky)
	//{
	//	auto templateID = ("@" + skyID);
	//	auto color = _fe3d->sky_getColor(skyID);
	//	auto rotation = _fe3d->sky_getRotation(skyID);
	//	auto lightness = _fe3d->sky_getInitialLightness(skyID);

	//	file <<
	//		"SKY " <<
	//		skyID << " " <<
	//		templateID << " " <<
	//		rotation << " " <<
	//		lightness << " " <<
	//		color.r << " " <<
	//		color.g << " " <<
	//		color.b << endl;
	//}

	//string terrainID = _fe3d->terrain_getSelectedID();
	//if(!terrainID.empty() && _hasCustomWorldTerrain)
	//{
	//	string templateID = ("@" + terrainID);

	//	file <<
	//		"TERRAIN " <<
	//		terrainID << " " <<
	//		templateID << endl;
	//}

	//string waterID = _fe3d->water_getSelectedID();
	//if(!waterID.empty() && _hasCustomWorldWater)
	//{
	//	string templateID = ("@" + waterID);
	//	auto color = _fe3d->water_getColor(waterID);
	//	auto speed = _fe3d->water_getSpeed(waterID);
	//	auto transparency = _fe3d->water_getTransparency(waterID);

	//	file <<
	//		"WATER " <<
	//		waterID << " " <<
	//		templateID << " " <<
	//		color.r << " " <<
	//		color.g << " " <<
	//		color.b << " " <<
	//		speed.x << " " <<
	//		speed.y << " " <<
	//		transparency << endl;
	//}

	//for(const auto& modelID : _fe3d->model_getIDs())
	//{
	//	bool isLevelOfDetailEntity = find(levelOfDetailEntityIDs.begin(), levelOfDetailEntityIDs.end(), modelID) != levelOfDetailEntityIDs.end();
	//	bool isCustomWorldModel =
	//		find(_customWorldModelIDs.begin(), _customWorldModelIDs.end(), modelID) != _customWorldModelIDs.end();
	//	if(((modelID[0] != '@') || isLevelOfDetailEntity) && isCustomWorldModel)
	//	{
	//		auto aabbIDs = _fe3d->aabb_getChildIDs(modelID, AabbParentEntityType::MODEL);

	//		auto isVisible = _fe3d->model_isVisible(modelID);
	//		auto isFrozen = _fe3d->model_isFrozen(modelID);
	//		auto isAabbRaycastResponsive = aabbIDs.empty() ? false : _fe3d->aabb_isRaycastResponsive(aabbIDs[0]);
	//		auto isAabbCollisionResponsive = aabbIDs.empty() ? false : _fe3d->aabb_isCollisionResponsive(aabbIDs[0]);
	//		auto position = _fe3d->model_getBasePosition(modelID);
	//		auto rotation = _fe3d->model_getBaseRotation(modelID);
	//		auto rotationOrigin = _fe3d->model_getBaseRotationOrigin(modelID);
	//		auto size = _fe3d->model_getBaseSize(modelID);
	//		auto color = _fe3d->model_getColor(modelID, "");
	//		auto minHeight = _fe3d->model_getMinHeight(modelID);
	//		auto maxHeight = _fe3d->model_getMaxHeight(modelID);
	//		auto transparency = _fe3d->model_getTransparency(modelID, "");
	//		auto lightness = _fe3d->model_getLightness(modelID, "");

	//		string templateID;
	//		if(_loadedModelIDs.find(modelID) == _loadedModelIDs.end())
	//		{
	//			templateID = _outsideLoadedModelIDs.at(modelID);
	//		}
	//		else
	//		{
	//			templateID = _loadedModelIDs.at(modelID);
	//		}

	//		file <<
	//			"MODEL " <<
	//			modelID << " " <<
	//			templateID << " " <<
	//			isVisible << " " <<
	//			isFrozen << " " <<
	//			isAabbRaycastResponsive << " " <<
	//			isAabbCollisionResponsive << " " <<
	//			position.x << " " <<
	//			position.y << " " <<
	//			position.z << " " <<
	//			rotation.x << " " <<
	//			rotation.y << " " <<
	//			rotation.z << " " <<
	//			rotationOrigin.x << " " <<
	//			rotationOrigin.y << " " <<
	//			rotationOrigin.z << " " <<
	//			size.x << " " <<
	//			size.y << " " <<
	//			size.z << " " <<
	//			color.r << " " <<
	//			color.g << " " <<
	//			color.b << " " <<
	//			minHeight << " " <<
	//			maxHeight << " " <<
	//			transparency << " " <<
	//			lightness << " " <<
	//			_fe3d->model_getPartIDs(modelID).size();

	//		auto partIDs = _fe3d->model_getPartIDs(modelID);
	//		if(partIDs.size() > 1)
	//		{
	//			for(const auto& partID : partIDs)
	//			{
	//				file << " ";

	//				file << partID;
	//			}

	//			for(size_t i = 0; i < partIDs.size(); i++)
	//			{
	//				if(!partIDs[i].empty())
	//				{
	//					file << " ";

	//					position = _fe3d->model_getPartPosition(modelID, partIDs[i]);
	//					rotation = _fe3d->model_getPartRotation(modelID, partIDs[i]);
	//					rotationOrigin = _fe3d->model_getPartRotationOrigin(modelID, partIDs[i]);
	//					size = _fe3d->model_getPartSize(modelID, partIDs[i]);

	//					file <<
	//						partIDs[i] << " " <<
	//						position.x << " " <<
	//						position.y << " " <<
	//						position.z << " " <<
	//						rotation.x << " " <<
	//						rotation.y << " " <<
	//						rotation.z << " " <<
	//						rotationOrigin.x << " " <<
	//						rotationOrigin.y << " " <<
	//						rotationOrigin.z << " " <<
	//						size.x << " " <<
	//						size.y << " " <<
	//						size.z;
	//				}
	//			}
	//		}

	//		file << endl;
	//	}
	//}

	//for(const auto& modelID : _fe3d->model_getIDs())
	//{
	//	bool isLodModel = find(levelOfDetailEntityIDs.begin(), levelOfDetailEntityIDs.end(), modelID) != levelOfDetailEntityIDs.end();
	//	bool isCustomWorldModel =
	//		find(_customWorldModelIDs.begin(), _customWorldModelIDs.end(), modelID) != _customWorldModelIDs.end();
	//	if(((modelID[0] != '@') || isLodModel) && isCustomWorldModel)
	//	{
	//		//for(const auto& animationID : _animation3dEditor->getStartedModelAnimationIDs(modelID))
	//		//{
	//		//	// Retrieve raw animation data for retrieving
	//		//	string errorMessage = "Tried to retrieve animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";
	//		//	auto animationData = _animation3dEditor->getAnimationData(animationID, modelID, errorMessage);

	//		//	// Data to save
	//		//	auto isPaused = animationData->isPaused();
	//		//	auto frameIndex = animationData->getFrameIndex();
	//		//	auto speedMultiplier = animationData->getSpeedMultiplier();
	//		//	auto remainingLoops = (animationData->getPlayCount() == -1) ? -1 : (animationData->getPlayCount() - 1);
	//		//	auto fadeFramestep = animationData->getFadeFramestep();

	//		//	// Write main data
	//		//	file <<
	//		//		"ANIMATION " <<
	//		//		animationID << " " <<
	//		//		modelID << " " <<
	//		//		isPaused << " " <<
	//		//		frameIndex << " " <<
	//		//		speedMultiplier << " " <<
	//		//		remainingLoops << " " <<
	//		//		fadeFramestep << " ";

	//		//	// Write speeds
	//		//	unsigned int index = 0;
	//		//	auto frame = animationData->getFrames().at(animationData->getFrameIndex());
	//		//	for(const auto& [key, speed] : frame.getSpeeds())
	//		//	{
	//		//		// Write speed
	//		//		file << (partID.empty() ? "?" : partID) << " " << speed.x << " " << speed.y << " " << speed.z;

	//		//		// Write space
	//		//		if(index != (frame.getSpeeds().size() - 1))
	//		//		{
	//		//			file << " ";
	//		//		}
	//		//		index++;
	//		//	}

	//		//	file << endl;
	//		//}
	//	}
	//}

	//for(const auto& quad3dID : _fe3d->quad3d_getIDs())
	//{
	//	bool isCustomWorldBillboard =
	//		find(_customWorldQuad3dIDs.begin(), _customWorldQuad3dIDs.end(), quad3dID) != _customWorldQuad3dIDs.end();
	//	if((quad3dID[0] != '@') && isCustomWorldBillboard)
	//	{
	//		auto aabbIDs = _fe3d->aabb_getChildIDs(quad3dID, AabbParentEntityType::QUAD3D);

	//		auto isVisible = _fe3d->quad3d_isVisible(quad3dID);
	//		auto isAabbRaycastResponsive = aabbIDs.empty() ? false : _fe3d->aabb_isRaycastResponsive(aabbIDs[0]);
	//		auto isAabbCollisionResponsive = aabbIDs.empty() ? false : _fe3d->aabb_isCollisionResponsive(aabbIDs[0]);
	//		auto isFacingX = _fe3d->quad3d_isFacingCameraX(quad3dID);
	//		auto isFacingY = _fe3d->quad3d_isFacingCameraY(quad3dID);
	//		//auto isAnimationPlaying = _fe3d->quad3d_isSpriteAnimationStarted(quad3dID);
	//		//auto isAnimationPaused = _fe3d->quad3d_isSpriteAnimationPaused(quad3dID);
	//		auto position = _fe3d->quad3d_getPosition(quad3dID);
	//		auto rotation = _fe3d->quad3d_getRotation(quad3dID);
	//		auto size = _fe3d->quad3d_getSize(quad3dID);
	//		auto color = _fe3d->quad3d_getColor(quad3dID);
	//		//auto textContent = _fe3d->quad3d_getTextContent(quad3dID);
	//		auto lightness = _fe3d->quad3d_getLightness(quad3dID);
	//		auto minHeight = _fe3d->quad3d_getMinHeight(quad3dID);
	//		auto maxHeight = _fe3d->quad3d_getMaxHeight(quad3dID);
	//		//auto remainingAnimationLoops = _fe3d->quad3d_getRemainingSpriteAnimationLoops(quad3dID);
	//		//auto animationRowIndex = _fe3d->quad3d_getSpriteAnimationRowIndex(quad3dID);
	//		//auto animationColumnIndex = _fe3d->quad3d_getSpriteAnimationColumnIndex(quad3dID);

	//		//textContent = (textContent.empty()) ? "?" : textContent;

	//		//replace(textContent.begin(), textContent.end(), ' ', '?');

	//		string templateID;
	//		if(_loadedQuad3dIDs.find(quad3dID) == _loadedQuad3dIDs.end())
	//		{
	//			templateID = _outsideLoadedQuad3dIDs.at(quad3dID);
	//		}
	//		else
	//		{
	//			templateID = _loadedQuad3dIDs.at(quad3dID);
	//		}

	//		file <<
	//			"BILLBOARD " <<
	//			quad3dID << " " <<
	//			templateID << " " <<
	//			isVisible << " " <<
	//			isAabbRaycastResponsive << " " <<
	//			isAabbCollisionResponsive << " " <<
	//			isFacingX << " " <<
	//			isFacingY << " " <<
	//			position.x << " " <<
	//			position.y << " " <<
	//			position.z << " " <<
	//			rotation.x << " " <<
	//			rotation.y << " " <<
	//			rotation.z << " " <<
	//			size.x << " " <<
	//			size.y << " " <<
	//			color.r << " " <<
	//			color.g << " " <<
	//			color.b << " " <<
	//			textContent << " " <<
	//			lightness << " " <<
	//			minHeight << " " <<
	//			maxHeight << endl;
	//	}
	//}

	//for(const auto& aabbID : _fe3d->aabb_getIDs())
	//{
	//	bool isCustomWorldAabb =
	//		find(_customWorldAabbIDs.begin(), _customWorldAabbIDs.end(), aabbID) != _customWorldAabbIDs.end();
	//	if((aabbID[0] != '@') && isCustomWorldAabb && _fe3d->aabb_getParentEntityID(aabbID).empty())
	//	{
	//		auto isVisible = _fe3d->aabb_isVisible(aabbID);
	//		auto isRaycastResponsive = _fe3d->aabb_isRaycastResponsive(aabbID);
	//		auto isCollisionResponsive = _fe3d->aabb_isCollisionResponsive(aabbID);
	//		auto position = _fe3d->aabb_getPosition(aabbID);
	//		auto size = _fe3d->aabb_getSize(aabbID);

	//		file <<
	//			"AABB " <<
	//			aabbID << " " <<
	//			isVisible << " " <<
	//			isRaycastResponsive << " " <<
	//			isCollisionResponsive << " " <<
	//			position.x << " " <<
	//			position.y << " " <<
	//			position.z << " " <<
	//			size.x << " " <<
	//			size.y << " " <<
	//			size.z << endl;
	//	}
	//}

	////for(const auto& soundID : _fe3d->sound3d_getIDs())
	////{
	////	// Check if allowed to save
	////	bool isCustomWorldSound =
	////		find(_customWorldSoundIDs.begin(), _customWorldSoundIDs.end(), soundID) != _customWorldSoundIDs.end();
	////	if((soundID[0] != '@') && isCustomWorldSound && _fe3d->sound_is3D(soundID))
	////	{
	////		// Data to save
	////		auto position = _fe3d->sound_getPosition(soundID);
	////		auto maxVolume = _fe3d->sound_getMaxVolume(soundID);
	////		auto maxDistance = _fe3d->sound_getMaxDistance(soundID);

	////		// Extract template ID
	////		string templateID;
	////		if(_loadedSoundIDs.find(soundID) == _loadedSoundIDs.end())
	////		{
	////			templateID = _outsideLoadedSoundIDs.at(soundID);
	////		}
	////		else
	////		{
	////			templateID = _loadedSoundIDs.at(soundID);
	////		}

	////		// Write data
	////		file <<
	////			"SOUND " <<
	////			soundID << " " <<
	////			templateID << " " <<
	////			position.x << " " <<
	////			position.y << " " <<
	////			position.z << " " <<
	////			maxVolume << " " <<
	////			maxDistance << endl;
	////	}
	////}

	//for(const auto& pointlightID : _fe3d->pointlight_getIDs())
	//{
	//	bool isCustomWorldPointlight =
	//		find(_customWorldPointlightIDs.begin(), _customWorldPointlightIDs.end(), pointlightID) != _customWorldPointlightIDs.end();
	//	if((pointlightID[0] != '@') && isCustomWorldPointlight)
	//	{
	//		auto position = _fe3d->pointlight_getPosition(pointlightID);
	//		auto radius = _fe3d->pointlight_getRadius(pointlightID);
	//		auto color = _fe3d->pointlight_getColor(pointlightID);
	//		auto intensity = _fe3d->pointlight_getIntensity(pointlightID);

	//		file <<
	//			"POINTLIGHT " <<
	//			pointlightID << " " <<
	//			position.x << " " <<
	//			position.y << " " <<
	//			position.z << " " <<
	//			radius.x << " " <<
	//			radius.y << " " <<
	//			radius.z << " " <<
	//			color.r << " " <<
	//			color.g << " " <<
	//			color.b << " " <<
	//			intensity << endl;
	//	}
	//}

	//for(const auto& spotlightID : _fe3d->spotlight_getIDs())
	//{
	//	bool isCustomWorldSpotlight =
	//		find(_customWorldSpotlightIDs.begin(), _customWorldSpotlightIDs.end(), spotlightID) != _customWorldSpotlightIDs.end();
	//	if((spotlightID[0] != '@') && isCustomWorldSpotlight)
	//	{
	//		auto position = _fe3d->spotlight_getPosition(spotlightID);
	//		auto color = _fe3d->spotlight_getColor(spotlightID);
	//		auto yaw = _fe3d->spotlight_getYaw(spotlightID);
	//		auto pitch = _fe3d->spotlight_getPitch(spotlightID);
	//		auto intensity = _fe3d->spotlight_getIntensity(spotlightID);
	//		auto angle = _fe3d->spotlight_getAngle(spotlightID);
	//		auto distance = _fe3d->spotlight_getDistance(spotlightID);

	//		file <<
	//			"SPOTLIGHT " <<
	//			spotlightID << " " <<
	//			position.x << " " <<
	//			position.y << " " <<
	//			position.z << " " <<
	//			color.r << " " <<
	//			color.g << " " <<
	//			color.b << " " <<
	//			yaw << " " <<
	//			pitch << " " <<
	//			intensity << " " <<
	//			angle << " " <<
	//			distance << endl;
	//	}
	//}

	//for(const auto& reflectionID : _fe3d->reflection_getIDs())
	//{
	//	bool isCustomWorldReflection =
	//		find(_customWorldReflectionIDs.begin(), _customWorldReflectionIDs.end(), reflectionID) != _customWorldReflectionIDs.end();
	//	if((reflectionID[0] != '@') && isCustomWorldReflection)
	//	{
	//		auto position = _fe3d->reflection_getPosition(reflectionID);

	//		file <<
	//			"REFLECTION " <<
	//			reflectionID << " " <<
	//			position.x << " " <<
	//			position.y << " " <<
	//			position.z << endl;
	//	}
	//}

	//if(_hasCustomWorldLighting)
	//{
	//	if(_fe3d->gfx_isAmbientLightingEnabled())
	//	{
	//		auto ambientLightingColor = _fe3d->gfx_getAmbientLightingColor();
	//		auto ambientLightingIntensity = _fe3d->gfx_getAmbientLightingIntensity();

	//		file <<
	//			"LIGHTING_AMBIENT " <<
	//			ambientLightingColor.r << " " <<
	//			ambientLightingColor.g << " " <<
	//			ambientLightingColor.b << " " <<
	//			ambientLightingIntensity << endl;
	//	}

	//	if(_fe3d->gfx_isDirectionalLightingEnabled())
	//	{
	//		auto directionalLightingColor = _fe3d->gfx_getDirectionalLightingColor();
	//		auto directionalLightingPosition = _fe3d->gfx_getDirectionalLightingPosition();
	//		auto directionalLightingIntensity = _fe3d->gfx_getDirectionalLightingIntensity();

	//		file <<
	//			"LIGHTING_DIRECTIONAL " <<
	//			directionalLightingPosition.x << " " <<
	//			directionalLightingPosition.y << " " <<
	//			directionalLightingPosition.z << " " <<
	//			directionalLightingColor.r << " " <<
	//			directionalLightingColor.g << " " <<
	//			directionalLightingColor.b << " " <<
	//			directionalLightingIntensity << endl;
	//	}
	//}

	//if(_hasCustomWorldGraphics)
	//{
	//	if(_fe3d->gfx_isShadowsEnabled())
	//	{
	//		auto size = _fe3d->gfx_getShadowSize();
	//		auto lightness = _fe3d->gfx_getShadowLightness();
	//		auto eye = _fe3d->gfx_getShadowEyePosition();
	//		auto center = _fe3d->gfx_getShadowCenterPosition();
	//		auto isFollowingCamera = _fe3d->gfx_isShadowFollowingCamera();
	//		auto interval = _fe3d->gfx_getShadowInterval();

	//		file <<
	//			"GRAPHICS_SHADOWS " <<
	//			size << " " <<
	//			lightness << " " <<
	//			Tools::vec2str(eye) << " " <<
	//			Tools::vec2str(center) << " " <<
	//			isFollowingCamera << " " <<
	//			interval << endl;
	//	}

	//	if(_fe3d->gfx_isMotionBlurEnabled())
	//	{
	//		file << "GRAPHICS_MOTION_BLUR " << _fe3d->gfx_getMotionBlurStrength() << endl;
	//	}

	//	if(_fe3d->gfx_isDofEnabled())
	//	{
	//		auto dynamic = _fe3d->gfx_isDofDynamic();
	//		auto blurDistance = _fe3d->gfx_getDofBlurDistance();
	//		auto maxDistance = _fe3d->gfx_getDofDynamicDistance();

	//		file <<
	//			"GRAPHICS_DOF " <<
	//			dynamic << " " <<
	//			blurDistance << " " <<
	//			maxDistance << endl;
	//	}

	//	if(_fe3d->gfx_isFogEnabled())
	//	{
	//		auto minDistance = _fe3d->gfx_getFogMinDistance();
	//		auto maxDistance = _fe3d->gfx_getFogMaxDistance();
	//		auto thickness = _fe3d->gfx_getFogThickness();
	//		auto color = _fe3d->gfx_getFogColor();

	//		file <<
	//			"GRAPHICS_FOG " <<
	//			minDistance << " " <<
	//			maxDistance << " " <<
	//			thickness << " " <<
	//			Tools::vec2str(color) << endl;
	//	}

	//	if(_fe3d->gfx_isLensFlareEnabled())
	//	{
	//		auto flareMapPath = _fe3d->gfx_getLensFlareMapPath();
	//		auto intensity = _fe3d->gfx_getLensFlareIntensity();
	//		auto sensitivity = _fe3d->gfx_getLensFlareSensitivity();

	//		flareMapPath = (flareMapPath.empty()) ? "?" : flareMapPath;

	//		replace(flareMapPath.begin(), flareMapPath.end(), ' ', '?');

	//		file <<
	//			"GRAPHICS_LENS_FLARE " <<
	//			flareMapPath << " " <<
	//			intensity << " " <<
	//			sensitivity << endl;
	//	}

	//	if(_fe3d->gfx_isSkyExposureEnabled())
	//	{
	//		file << "GRAPHICS_SKY_EXPOSURE " << _fe3d->gfx_getSkyExposureIntensity() << " " << _fe3d->gfx_getSkyExposureSpeed() << endl;
	//	}

	//	if(_fe3d->gfx_isBloomEnabled())
	//	{
	//		auto type = static_cast<unsigned int>(_fe3d->gfx_getBloomType());
	//		auto intensity = _fe3d->gfx_getBloomIntensity();
	//		auto blurCount = _fe3d->gfx_getBloomBlurCount();

	//		file <<
	//			"GRAPHICS_BLOOM " <<
	//			type << " " <<
	//			intensity << " " <<
	//			blurCount << endl;
	//	}
	//}

	//file.close();

	//_customWorldID = "";
	//_hasCustomWorldLighting = false;
	//_hasCustomWorldGraphics = false;
	//_hasCustomWorldSky = false;
	//_hasCustomWorldTerrain = false;
	//_hasCustomWorldWater = false;
	//_customWorldModelIDs.clear();
	//_customWorldQuad3dIDs.clear();
	//_customWorldAabbIDs.clear();
	//_customWorldSoundIDs.clear();
	//_customWorldPointlightIDs.clear();
	//_customWorldSpotlightIDs.clear();

	return true;
}