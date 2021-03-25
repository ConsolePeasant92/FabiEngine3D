#include "scene_editor.hpp"

#include <fstream>
#include <algorithm>

void SceneEditor::loadCustomSceneFromFile(const string& fileName)
{
	// Error checking
	if (_currentProjectID == "")
	{
		_fe3d.logger_throwError("No current project loaded --> SceneEditor::loadCustomSceneFromFile()");
	}
	if (_isEditorLoaded)
	{
		_fe3d.logger_throwWarning("Tried to call saveCustomSceneToFile() from within scene editor!");
	}

	// Check if scene directory still exists
	string directoryPath = _fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\scenes\\";
	if (!_fe3d.misc_isDirectoryExisting(directoryPath) || !_fe3d.misc_isDirectoryExisting(directoryPath + "editor\\"))
	{
		_fe3d.logger_throwWarning("Project \"" + _currentProjectID + "\" corrupted: scenes folder(s) missing!");
	}

	// Check if scene file exists
	string fullFilePath = string(directoryPath + "editor\\" + fileName + ".fe3d");
	if (_fe3d.misc_isFileExisting(fullFilePath))
	{
		// Clear last scene data
		_loadedSceneID = fileName;
		_loadedSkyID = "";
		_loadedTerrainID = "";
		_loadedWaterID = "";
		_loadedModelIDs.clear();
		_loadedBillboardIDs.clear();
		_loadedAudioIDs.clear();
		_loadedLightIDs.clear();

		// Load scene file
		std::ifstream file(fullFilePath);
		string line;

		// Read model data
		while (std::getline(file, line))
		{
			// For file extraction
			std::istringstream iss(line);

			// Extract type from file
			string entityType;
			iss >>
				entityType;

			// Load entity according to type
			if (entityType == "SKY")
			{
				// Data placeholders
				string skyID, previewID;
				float rotationSpeed, lightness;
				Vec3 color;

				// Extract data
				iss >>
					skyID >>
					previewID >>
					rotationSpeed >>
					lightness >>
					color.r >>
					color.g >>
					color.b;

				// Add sky
				_copyPreviewSky(skyID, previewID);
				_fe3d.skyEntity_setRotationSpeed(skyID, rotationSpeed);
				_fe3d.skyEntity_setLightness(skyID, lightness);
				_fe3d.skyEntity_setColor(skyID, color);
				std::cout << _fe3d.skyEntity_getSelectedID() << std::endl;
			}
			else if (entityType == "TERRAIN")
			{
				// Data placeholders
				string terrainID, previewID;

				// Extract data
				iss >>
					terrainID >>
					previewID;

				// Add terrain
				_copyPreviewTerrain(terrainID, previewID);
			}
			else if (entityType == "WATER")
			{
				// Data placeholders
				string waterID, previewID;
				Vec3 color;
				Vec2 speed;
				float transparency;

				// Extract data
				iss >>
					waterID >>
					previewID >>
					color.r >>
					color.g >>
					color.b >>
					speed.x >>
					speed.y >>
					transparency;

				// Add water
				_copyPreviewWater(waterID, previewID);
				_fe3d.waterEntity_setColor(waterID, color);
				_fe3d.waterEntity_setSpeed(waterID, speed);
				_fe3d.waterEntity_setTransparency(waterID, transparency);
			}
			else if (entityType == "MODEL")
			{
				// Data placeholders
				string modelID, previewID;
				Vec3 position, rotation, rotationOrigin, size, color;
				float minHeight, maxHeight, alpha, lightness;
				bool isVisible, isFrozen, isAabbRaycastResponsive, isAabbCollisionResponsive;

				// Extract ID
				iss >>
					modelID;

				// Check if LOD entitty
				bool makeInvisible = modelID[0] == '@';

				// Extract main data
				iss >>
					previewID >>
					isVisible >>
					isFrozen >>
					isAabbRaycastResponsive >>
					isAabbCollisionResponsive >>
					position.x >>
					position.y >>
					position.z >>
					rotation.x >>
					rotation.y >>
					rotation.z >>
					rotationOrigin.x >>
					rotationOrigin.y >>
					rotationOrigin.z >>
					size.x >>
					size.y >>
					size.z >>
					color.r >>
					color.g >>
					color.b >>
					minHeight >>
					maxHeight >>
					alpha >>
					lightness;

				// Add model
				_copyPreviewModel(modelID, previewID, position);
				_fe3d.modelEntity_setRotation(modelID, rotation);
				_fe3d.modelEntity_setRotationOrigin(modelID, rotationOrigin);
				_fe3d.modelEntity_setSize(modelID, size);
				_fe3d.modelEntity_setStaticToCamera(modelID, isFrozen);
				_fe3d.modelEntity_setColor(modelID, color);
				_fe3d.modelEntity_setMinHeight(modelID, minHeight);
				_fe3d.modelEntity_setMaxHeight(modelID, maxHeight);
				_fe3d.modelEntity_setAlpha(modelID, alpha);
				_fe3d.modelEntity_setLightness(modelID, lightness);
				!isVisible ? _fe3d.modelEntity_hide(modelID) : void(0);
				for (auto& ID : _fe3d.aabbEntity_getBoundIDs(modelID, true, false))
				{
					_fe3d.aabbEntity_setRaycastResponsive(ID, isAabbRaycastResponsive);
					_fe3d.aabbEntity_setCollisionResponsive(ID, isAabbCollisionResponsive);
				}

				// Extract instanced offsets
				if (_fe3d.modelEntity_isInstanced(modelID))
				{
					vector<Vec3> instancedOffsets;
					while (true)
					{
						// Check if file has offset data left
						string nextElement;
						iss >>
							nextElement;

						// Check if item is a number
						if (nextElement == "") // End of line, because instanced model cannot have AABB
						{
							break;
						}
						else // Add offset
						{
							Vec3 offset;
							offset.x = stof(nextElement);
							iss >>
								offset.y >>
								offset.z;
							instancedOffsets.push_back(offset);
						}
					}

					// Add offsets
					_fe3d.modelEntity_setInstanced(modelID, true, instancedOffsets);
				}

				// Hide model if LOD
				if (makeInvisible)
				{
					_fe3d.modelEntity_hide(modelID);
				}
			}
			else if (entityType == "BILLBOARD")
			{
				// Data placeholders
				string billboardID, previewID, textContent;
				Vec3 position, rotation, color;
				Vec2 size;
				float lightness, minHeight, maxHeight;
				bool isVisible, isAabbRaycastResponsive, isAabbCollisionResponsive, isFacingX, isFacingY;

				// Extract data
				iss >>
					billboardID >>
					previewID >>
					isVisible >>
					isAabbRaycastResponsive >>
					isAabbCollisionResponsive >>
					isFacingX >>
					isFacingY >>
					position.x >>
					position.y >>
					position.z >>
					rotation.x >>
					rotation.y >>
					rotation.z >>
					size.x >>
					size.y >>
					color.r >>
					color.g >>
					color.b >>
					textContent >>
					lightness >>
					minHeight >>
					maxHeight;

				// Add billboard
				_copyPreviewBillboard(billboardID, previewID, position);
				_fe3d.billboardEntity_setRotation(billboardID, rotation);
				_fe3d.billboardEntity_setSize(billboardID, size);
				_fe3d.billboardEntity_setCameraFacingX(billboardID, isFacingX);
				_fe3d.billboardEntity_setCameraFacingY(billboardID, isFacingY);
				_fe3d.billboardEntity_setColor(billboardID, color);
				_fe3d.billboardEntity_setTextContent(billboardID, textContent);
				_fe3d.billboardEntity_setLightness(billboardID, lightness);
				_fe3d.billboardEntity_setMinHeight(billboardID, minHeight);
				_fe3d.billboardEntity_setMaxHeight(billboardID, maxHeight);
				!isVisible ? _fe3d.modelEntity_hide(billboardID) : void(0);
				for (auto& ID : _fe3d.aabbEntity_getBoundIDs(billboardID, false, true))
				{
					_fe3d.aabbEntity_setRaycastResponsive(ID, isAabbRaycastResponsive);
					_fe3d.aabbEntity_setCollisionResponsive(ID, isAabbCollisionResponsive);
				}
			}
			else if (entityType == "AUDIO")
			{
				// Data placeholders
				string audioID, previewID;
				Vec3 position;
				float maxVolume, maxDistance;

				// Extract data
				iss >>
					audioID >>
					previewID >>
					position.x >>
					position.y >>
					position.z >>
					maxVolume >>
					maxDistance;

				// Add audio
				_fe3d.audioEntity_add3D(audioID, _fe3d.audioEntity_getFilePath(previewID), position, maxVolume, maxDistance);
				_fe3d.audioEntity_play(audioID, -1, 0.0f);
				_loadedAudioIDs.insert(make_pair(audioID, previewID));
			}
			else if (entityType == "AMBIENT_LIGHT")
			{
				// Values
				Vec3 ambientLightingColor;
				float ambientLightingIntensity;

				// Extract
				iss >>
					ambientLightingColor.r >>
					ambientLightingColor.g >>
					ambientLightingColor.b >>
					ambientLightingIntensity;

				// Apply
				_fe3d.gfx_enableAmbientLighting(ambientLightingColor, ambientLightingIntensity);
			}
			else if (entityType == "DIRECTIONAL_LIGHT")
			{
				// Data placeholders
				Vec3 directionalLightingPosition, directionalLightingColor;
				float directionalLightingIntensity, billboardSize, billboardLightness;

				// Extract data
				iss >>
					directionalLightingPosition.x >>
					directionalLightingPosition.y >>
					directionalLightingPosition.z >>
					directionalLightingColor.r >>
					directionalLightingColor.g >>
					directionalLightingColor.b >>
					directionalLightingIntensity >>
					billboardSize >>
					billboardLightness;

				// Add directional lighting
				_fe3d.gfx_enableDirectionalLighting(directionalLightingPosition, directionalLightingColor, directionalLightingIntensity);

				// Set lightsource billboard
				_fe3d.billboardEntity_setPosition("@@lightSource", directionalLightingPosition);
				_fe3d.billboardEntity_setSize("@@lightSource", Vec2(billboardSize));
				_fe3d.billboardEntity_setLightness("@@lightSource", billboardLightness);
				_fe3d.billboardEntity_setColor("@@lightSource", directionalLightingColor);
				_fe3d.billboardEntity_setDepthMapIncluded("@@lightSource", false);
				_fe3d.billboardEntity_show("@@lightSource");
			}
			else if (entityType == "POINT_LIGHT")
			{
				// Data placeholders
				string lightID;
				Vec3 position, color;
				float intensity, distance;

				// Extract data
				iss >>
					lightID >>
					position.x >>
					position.y >>
					position.z >>
					color.r >>
					color.g >>
					color.b >>
					intensity >>
					distance;

				// Add point light
				_fe3d.lightEntity_add(lightID, position, color, intensity, distance);
				_loadedLightIDs.push_back(lightID);
			}
			else if (entityType == "LOD_DISTANCE")
			{
				// Data placeholders
				float lodDistance;

				// Extract data
				iss >>
					lodDistance;

				// Set distance
				_fe3d.misc_setLevelOfDetailDistance(lodDistance);
			}
			else if (entityType == "EDITOR_SPEED")
			{
				// Extract data
				iss >>
					_customEditorSpeed;
			}
			else if (entityType == "EDITOR_POSITION")
			{
				// Data placeholders
				Vec3 position;

				// Extract data
				iss >>
					position.x >>
					position.y >>
					position.z;

				// Set position
				_fe3d.camera_setPosition(position);
			}
			else if (entityType == "EDITOR_YAW")
			{
				// Data placeholders
				float yaw;
				iss >>
					yaw;

				// Set yaw
				_fe3d.camera_setYaw(yaw);
			}
			else if (entityType == "EDITOR_PITCH")
			{
				// Data placeholders
				float pitch;

				// Extract data
				iss >>
					pitch;

				// Set pitch
				_fe3d.camera_setPitch(pitch);
			}
			else if (entityType == "GRAPHICS_SHADOWS")
			{
				// Data placeholders
				bool enabled;
				float size, lightness;
				Vec3 position, center;
				bool isFollowingCamera;
				bool isSoftShadowed;
				int interval;

				// Extract data
				iss >>
					enabled >>
					size >>
					lightness >>
					position.x >>
					position.y >>
					position.z >>
					center.x >>
					center.y >>
					center.z >>
					isFollowingCamera >>
					isSoftShadowed >>
					interval;

				// Enable shadows
				_fe3d.gfx_enableShadows(position, center, size, size * 2.0f, lightness, isFollowingCamera, isSoftShadowed, interval);
			}
			else if (entityType == "GRAPHICS_MOTIONBLUR")
			{
				// Data placeholders
				bool enabled;
				float strength;

				// Extract data
				iss >>
					enabled >>
					strength;

				// Enable motion blur
				_fe3d.gfx_enableMotionBlur(strength);
			}
			else if (entityType == "GRAPHICS_DOF")
			{
				// Data placeholders
				bool enabled, dynamic;
				float blurDistance, maxDistance;

				// Extract data
				iss >>
					enabled >>
					dynamic >>
					blurDistance >>
					maxDistance;

				// Enable DOF
				_fe3d.gfx_enableDOF(dynamic, maxDistance, blurDistance);
			}
			else if (entityType == "GRAPHICS_FOG")
			{
				// Data placeholders
				bool enabled;
				float minDistance, maxDistance, thickness;
				Vec3 color;

				// Extract data
				iss >>
					enabled >>
					minDistance >>
					maxDistance >>
					thickness >>
					color.r >>
					color.g >>
					color.b;

				// Enable fog
				_fe3d.gfx_enableFog(minDistance, maxDistance, thickness, color);
			}
			else if (entityType == "GRAPHICS_LENSFLARE")
			{
				// Data placeholders
				bool enabled;
				string flareMapPath;
				float intensity, multiplier;

				// Extract data
				iss >>
					enabled >>
					flareMapPath >>
					intensity >>
					multiplier;

				// Perform empty string & space conversions
				flareMapPath = (flareMapPath == "?") ? "" : flareMapPath;
				std::replace(flareMapPath.begin(), flareMapPath.end(), '?', ' ');

				// Enable lens flare
				_fe3d.gfx_enableLensFlare(flareMapPath, intensity, multiplier);
			}
			else if (entityType == "GRAPHICS_SKYHDR")
			{
				// Data placeholders
				bool enabled;
				float intensity;

				// Extract data
				iss >>
					enabled >>
					intensity;

				// Enable skyHDR
				_fe3d.gfx_enableSkyHDR(intensity);
			}
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Scene data from project \"" + _currentProjectID + "\" loaded!");
	}
	else
	{
		_fe3d.logger_throwWarning("Could not load scene \"" + fileName + "\"!");
	}
}