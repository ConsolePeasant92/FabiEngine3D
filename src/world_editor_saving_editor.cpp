#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::ofstream;

const bool WorldEditor::saveEditorWorldToFile()
{
	// Must be editing a world
	if(_currentWorldID.empty())
	{
		return false;
	}

	// Validate project ID
	if(_currentProjectID.empty())
	{
		Logger::throwError("WorldEditor::saveEditorWorldToFile");
	}

	// Create or overwrite file
	ofstream file(Tools::getRootDirectoryPath() + "projects\\" + _currentProjectID + "\\worlds\\editor\\" + _currentWorldID + ".fe3d");

	// Save all level of detail entity IDs
	vector<string> levelOfDetailEntityIDs;
	for(const auto& modelID : _fe3d.model_getIDs())
	{
		// Cannot be template
		if(modelID[0] != '@')
		{
			// Check if entity has level of detail model
			if(!_fe3d.model_getLevelOfDetailEntityID(modelID).empty())
			{
				// Check if ID not already added to list
				if(find(levelOfDetailEntityIDs.begin(), levelOfDetailEntityIDs.end(), modelID) == levelOfDetailEntityIDs.end())
				{
					levelOfDetailEntityIDs.push_back(_fe3d.model_getLevelOfDetailEntityID(modelID));
				}
			}
		}
	}

	// Camera position
	const auto cameraPosition = _fe3d.camera_getPosition();
	file << "CAMERA_POSITION " << cameraPosition.x << " " << cameraPosition.y << " " << cameraPosition.z << endl;

	// Camera yaw
	file << "CAMERA_YAW " << _fe3d.camera_getYaw() << endl;

	// Camera pitch
	file << "CAMERA_PITCH " << _fe3d.camera_getPitch() << endl;

	// Sky
	string skyID = _fe3d.sky_getSelectedID();
	if(!skyID.empty())
	{
		// Data to save
		string templateID = ("@" + skyID);

		// Write data
		file <<
			"SKY " <<
			skyID << " " <<
			templateID << endl;
	}

	// Terrain
	string terrainID = _fe3d.terrain_getSelectedID();
	if(!terrainID.empty())
	{
		// Data to save
		string templateID = ("@" + terrainID);

		// Write data
		file <<
			"TERRAIN " <<
			terrainID << " " <<
			templateID << endl;
	}

	// Water
	string waterID = _fe3d.water_getSelectedID();
	if(!waterID.empty())
	{
		// Data to save
		string templateID = ("@" + waterID);
		auto height = _fe3d.water_getHeight(waterID);

		// Write data
		file <<
			"WATER " <<
			waterID << " " <<
			templateID << " " <<
			height << endl;
	}

	// Models
	for(const auto& modelID : _fe3d.model_getIDs())
	{
		// Check if allowed to save
		bool isLevelOfDetailEntity = find(levelOfDetailEntityIDs.begin(), levelOfDetailEntityIDs.end(), modelID) != levelOfDetailEntityIDs.end();
		if((modelID[0] != '@') || isLevelOfDetailEntity)
		{
			// Temporary values
			auto startedAnimations = _animation3dEditor.getStartedModelAnimationIDs(modelID);

			// Check if model has bound animation
			if(!startedAnimations.empty())
			{
				// Reset main transformation
				_fe3d.model_setBasePosition(modelID, _initialModelPosition[modelID]);
				_fe3d.model_setBaseRotationOrigin(modelID, fvec3(0.0f));
				_fe3d.model_setBaseRotation(modelID, _initialModelRotation[modelID]);
				_fe3d.model_setBaseSize(modelID, _initialModelSize[modelID]);

				// Reset part transformations
				for(const auto& partID : _fe3d.model_getPartIDs(modelID))
				{
					// Only named parts
					if(!partID.empty())
					{
						_fe3d.model_setPartPosition(modelID, partID, fvec3(0.0f));
						_fe3d.model_setPartRotationOrigin(modelID, partID, fvec3(0.0f));
						_fe3d.model_setPartRotation(modelID, partID, fvec3(0.0f));
						_fe3d.model_setPartSize(modelID, partID, fvec3(1.0f));
					}
				}
			}

			// Data to save
			auto position = _fe3d.model_getBasePosition(modelID);
			auto rotation = _fe3d.model_getBaseRotation(modelID);
			auto size = _fe3d.model_getBaseSize(modelID);
			auto isFrozen = _fe3d.model_isFrozen(modelID);
			auto animationID = (startedAnimations.empty()) ? "" : startedAnimations[0];

			// Convert empty string
			animationID = (animationID.empty()) ? "?" : animationID;

			// Convert spaces
			replace(animationID.begin(), animationID.end(), ' ', '?');

			// Extract template ID
			string templateID = _loadedModelIDs.at(modelID);

			// Write main data
			file <<
				"MODEL " <<
				modelID << " " <<
				templateID << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				rotation.x << " " <<
				rotation.y << " " <<
				rotation.z << " " <<
				size.x << " " <<
				size.y << " " <<
				size.z << " " <<
				isFrozen << " " <<
				animationID;

			// New line
			file << endl;
		}
	}

	// Billboards
	for(const auto& billboardID : _fe3d.billboard_getIDs())
	{
		// Check if allowed to save
		if(billboardID[0] != '@')
		{
			// Temporary values
			auto startedAnimations = _animation2dEditor.getStartedBillboardAnimationIDs(billboardID);

			// Data to save
			auto position = _fe3d.billboard_getPosition(billboardID);
			auto rotation = _fe3d.billboard_getRotation(billboardID);
			auto size = _fe3d.billboard_getSize(billboardID);
			auto animationID = (startedAnimations.empty() ? "" : startedAnimations[0]);

			// Convert empty string
			animationID = (animationID.empty()) ? "?" : animationID;

			// Convert spaces
			replace(animationID.begin(), animationID.end(), ' ', '?');

			// Extract template ID
			string templateID = _loadedBillboardIDs.at(billboardID);

			// Write data
			file <<
				"BILLBOARD " <<
				billboardID << " " <<
				templateID << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				rotation.x << " " <<
				rotation.y << " " <<
				rotation.z << " " <<
				size.x << " " <<
				size.y << " " <<
				animationID << endl;
		}
	}

	// Sounds
	for(const auto& soundID : _fe3d.sound3d_getIDs())
	{
		// Check if allowed to save
		if(soundID[0] != '@')
		{
			// Data to save
			auto position = _fe3d.sound3d_getPosition(soundID);
			auto maxVolume = _fe3d.sound3d_getMaxVolume(soundID);
			auto maxDistance = _fe3d.sound3d_getMaxDistance(soundID);

			// Extract template ID
			string templateID = _loadedSoundIDs.at(soundID);

			// Write data
			file <<
				"SOUND " <<
				soundID << " " <<
				templateID << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				maxVolume << " " <<
				maxDistance << endl;
		}
	}

	// Pointlights
	for(const auto& pointlightID : _fe3d.pointlight_getIDs())
	{
		// Check if allowed to save
		if(pointlightID[0] != '@')
		{
			// Data to save
			auto position = _fe3d.pointlight_getPosition(pointlightID);
			auto radius = _fe3d.pointlight_getRadius(pointlightID);
			auto color = _fe3d.pointlight_getColor(pointlightID);
			auto intensity = _fe3d.pointlight_getIntensity(pointlightID);
			auto shape = static_cast<unsigned int>(_fe3d.pointlight_getShape(pointlightID));

			// Write data
			file <<
				"POINTLIGHT " <<
				pointlightID << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				radius.x << " " <<
				radius.y << " " <<
				radius.z << " " <<
				color.r << " " <<
				color.g << " " <<
				color.b << " " <<
				intensity << " " <<
				shape << endl;
		}
	}

	// Spotlights
	for(const auto& spotlightID : _fe3d.spotlight_getIDs())
	{
		// Check if allowed to save
		if(spotlightID[0] != '@')
		{
			// Data to save
			auto position = _fe3d.spotlight_getPosition(spotlightID);
			auto color = _fe3d.spotlight_getColor(spotlightID);
			auto yaw = _fe3d.spotlight_getYaw(spotlightID);
			auto pitch = _fe3d.spotlight_getPitch(spotlightID);
			auto intensity = _fe3d.spotlight_getIntensity(spotlightID);
			auto angle = _fe3d.spotlight_getAngle(spotlightID);
			auto distance = _fe3d.spotlight_getDistance(spotlightID);

			// Write data
			file <<
				"SPOTLIGHT " <<
				spotlightID << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				color.r << " " <<
				color.g << " " <<
				color.b << " " <<
				yaw << " " <<
				pitch << " " <<
				intensity << " " <<
				angle << " " <<
				distance << endl;
		}
	}

	// Reflections
	for(const auto& reflectionID : _fe3d.reflection_getIDs())
	{
		// Check if allowed to save
		if(reflectionID[0] != '@')
		{
			// Data to save
			auto position = _fe3d.reflection_getPosition(reflectionID);

			// Write data
			file <<
				"REFLECTION " <<
				reflectionID << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << endl;
		}
	}

	// Editor camera speed
	{
		file <<
			"EDITOR_SPEED " <<
			_editorSpeed << endl;
	}

	// Ambient lighting
	if(_fe3d.gfx_isAmbientLightingEnabled())
	{
		// Data to save
		auto ambientLightingColor = _fe3d.gfx_getAmbientLightingColor();
		auto ambientLightingIntensity = _fe3d.gfx_getAmbientLightingIntensity();

		// Write data
		file <<
			"LIGHTING_AMBIENT " <<
			ambientLightingColor.r << " " <<
			ambientLightingColor.g << " " <<
			ambientLightingColor.b << " " <<
			ambientLightingIntensity << endl;
	}

	// Directional lighting
	if(_fe3d.gfx_isDirectionalLightingEnabled())
	{
		// Data to save
		auto directionalLightingColor = _fe3d.gfx_getDirectionalLightingColor();
		auto directionalLightingPosition = _fe3d.gfx_getDirectionalLightingPosition();
		auto directionalLightingIntensity = _fe3d.gfx_getDirectionalLightingIntensity();

		// Write data
		file <<
			"LIGHTING_DIRECTIONAL " <<
			directionalLightingPosition.x << " " <<
			directionalLightingPosition.y << " " <<
			directionalLightingPosition.z << " " <<
			directionalLightingColor.r << " " <<
			directionalLightingColor.g << " " <<
			directionalLightingColor.b << " " <<
			directionalLightingIntensity << endl;
	}

	// Shadow settings
	if(_fe3d.gfx_isShadowsEnabled())
	{
		// Data to save
		auto size = _fe3d.gfx_getShadowSize();
		auto lightness = _fe3d.gfx_getShadowLightness();
		auto eye = _fe3d.gfx_getShadowEyePosition();
		auto center = _fe3d.gfx_getShadowCenterPosition();
		auto isFollowingCamera = _fe3d.gfx_isShadowFollowingCamera();
		auto interval = _fe3d.gfx_getShadowInterval();
		auto quality = _fe3d.gfx_getShadowQuality();

		// Write data
		file <<
			"GRAPHICS_SHADOWS " <<
			size << " " <<
			lightness << " " <<
			Tools::vec2str(eye) << " " <<
			Tools::vec2str(center) << " " <<
			isFollowingCamera << " " <<
			interval << " " <<
			quality << endl;
	}

	// Reflections settings
	{
		auto planarHeight = _fe3d.gfx_getPlanarReflectionHeight();
		auto cubeQuality = _fe3d.gfx_getCubeReflectionQuality();
		auto planarQuality = _fe3d.gfx_getPlanarReflectionQuality();
		file <<
			"GRAPHICS_REFLECTIONS " <<
			planarHeight << " " <<
			cubeQuality << " " <<
			planarQuality << endl;
	}

	// Refractions settings
	{
		auto planarQuality = _fe3d.gfx_getPlanarReflectionQuality();
		file <<
			"GRAPHICS_REFRACTIONS " <<
			planarQuality << endl;
	}

	// DOF settings
	if(_fe3d.gfx_isDofEnabled())
	{
		// Data to save
		auto dynamic = _fe3d.gfx_isDofDynamic();
		auto blurDistance = _fe3d.gfx_getDofBlurDistance();
		auto maxDistance = _fe3d.gfx_getDofDynamicDistance();
		auto quality = _fe3d.gfx_getDofQuality();

		// Write data
		file <<
			"GRAPHICS_DOF " <<
			dynamic << " " <<
			blurDistance << " " <<
			maxDistance << " " <<
			quality << endl;
	}

	// Fog settings
	if(_fe3d.gfx_isFogEnabled())
	{
		// Data to save
		auto minDistance = _fe3d.gfx_getFogMinDistance();
		auto maxDistance = _fe3d.gfx_getFogMaxDistance();
		auto thickness = _fe3d.gfx_getFogThickness();
		auto color = _fe3d.gfx_getFogColor();

		// Write data
		file <<
			"GRAPHICS_FOG " <<
			minDistance << " " <<
			maxDistance << " " <<
			thickness << " " <<
			Tools::vec2str(color) << endl;
	}

	// Lens flare settings
	if(_fe3d.gfx_isLensFlareEnabled())
	{
		// Data to save
		auto flareMapPath = _fe3d.gfx_getLensFlareMapPath();
		auto intensity = _fe3d.gfx_getLensFlareIntensity();
		auto sensitivity = _fe3d.gfx_getLensFlareSensitivity();

		// Convert to short path
		flareMapPath = string(flareMapPath.empty() ? "" : flareMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

		// Convert empty string
		flareMapPath = (flareMapPath.empty()) ? "?" : flareMapPath;

		// Convert spaces
		replace(flareMapPath.begin(), flareMapPath.end(), ' ', '?');

		// Write data
		file <<
			"GRAPHICS_LENS_FLARE " <<
			flareMapPath << " " <<
			intensity << " " <<
			sensitivity << endl;
	}

	// Sky exposure settings
	if(_fe3d.gfx_isSkyExposureEnabled())
	{
		file <<
			"GRAPHICS_SKY_EXPOSURE " <<
			_fe3d.gfx_getSkyExposureIntensity() << " "
			<< _fe3d.gfx_getSkyExposureSpeed() << endl;
	}

	// Bloom settings
	if(_fe3d.gfx_isBloomEnabled())
	{
		// Data to save
		auto type = static_cast<unsigned int>(_fe3d.gfx_getBloomType());
		auto intensity = _fe3d.gfx_getBloomIntensity();
		auto blurCount = _fe3d.gfx_getBloomBlurCount();
		auto quality = _fe3d.gfx_getBloomQuality();

		// Write data
		file <<
			"GRAPHICS_BLOOM " <<
			type << " " <<
			intensity << " " <<
			blurCount << " " <<
			quality << endl;
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("World data saved!");

	// Return
	return true;
}