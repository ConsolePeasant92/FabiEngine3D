#include "model_editor.hpp"
#include "left_viewport_controller.hpp"
#include "logger.hpp"

#include <fstream>
#include <algorithm>

bool ModelEditor::saveModelEntitiesToFile()
{
	// Editor must be loaded
	if (!_isEditorLoaded)
	{
		return false;
	}

	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("ModelEditor::saveModelEntitiesToFile() ---> no current project loaded!");
	}

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\model.fe3d";

	// Create or overwrite model file
	std::ofstream file(filePath);

	// Write model data
	for (const auto& modelID : _loadedModelIDs)
	{
		// Check if a 3D entity for this model is existing
		if (_fe3d.modelEntity_isExisting(modelID))
		{
			// General data
			auto isMultiParted = _fe3d.modelEntity_isMultiParted(modelID);
			auto meshPath = _fe3d.modelEntity_getMeshPath(modelID);
			auto diffuseMapPath = isMultiParted ? "" : _fe3d.modelEntity_getDiffuseMapPath(modelID);
			auto emissionMapPath = isMultiParted ? "" : _fe3d.modelEntity_getEmissionMapPath(modelID);
			auto normalMapPath = isMultiParted ? "" : _fe3d.modelEntity_getNormalMapPath(modelID);
			auto reflectionMapPath = isMultiParted ? "" : _fe3d.modelEntity_getReflectionMapPath(modelID);
			auto modelSize = _fe3d.modelEntity_getSize(modelID);
			auto isFaceCulled = _fe3d.modelEntity_isFaceCulled(modelID);
			auto isTransparent = _fe3d.modelEntity_isTransparent(modelID);
			auto isSpecular = _fe3d.modelEntity_isSpecularLighted(modelID);
			auto specularFactor = _fe3d.modelEntity_getSpecularFactor(modelID);
			auto specularIntensity = _fe3d.modelEntity_getSpecularIntensity(modelID);
			auto lightness = _fe3d.modelEntity_getLightness(modelID);
			auto color = _fe3d.modelEntity_getColor(modelID);
			auto uvRepeat = _fe3d.modelEntity_getUvRepeat(modelID);
			auto lodEntityID = _fe3d.modelEntity_getLevelOfDetailEntityID(modelID);
			auto isInstanced = _fe3d.modelEntity_isInstanced(modelID);
			auto isBright = _fe3d.modelEntity_isBright(modelID);
			auto reflectionType = static_cast<unsigned int>(_fe3d.modelEntity_getReflectionType(modelID));

			// AABB data
			vector<string> aabbNames;
			vector<Vec3> aabbPositions;
			vector<Vec3> aabbSizes;
			if (!isInstanced)
			{
				for (const auto& aabbID : _fe3d.aabbEntity_getBoundIDs(modelID, true, false))
				{
					aabbNames.push_back(aabbID.substr(string(modelID + "_").size()));
					aabbPositions.push_back(_fe3d.aabbEntity_getPosition(aabbID));
					aabbSizes.push_back(_fe3d.aabbEntity_getSize(aabbID));
				}
			}

			// Perform empty string & space conversions
			meshPath = (meshPath == "") ? "?" : meshPath;
			diffuseMapPath = (diffuseMapPath == "") ? "?" : diffuseMapPath;
			emissionMapPath = (emissionMapPath == "") ? "?" : emissionMapPath;
			reflectionMapPath = (reflectionMapPath == "") ? "?" : reflectionMapPath;
			normalMapPath = (normalMapPath == "") ? "?" : normalMapPath;
			lodEntityID = (lodEntityID == "") ? "?" : lodEntityID;
			std::replace(meshPath.begin(), meshPath.end(), ' ', '?');
			std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
			std::replace(emissionMapPath.begin(), emissionMapPath.end(), ' ', '?');
			std::replace(reflectionMapPath.begin(), reflectionMapPath.end(), ' ', '?');
			std::replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');
			std::replace(lodEntityID.begin(), lodEntityID.end(), ' ', '?');

			// NOTE: 1 model -> 1 line in file

			// Write general data
			file <<
				modelID << " " <<
				meshPath << " " <<
				diffuseMapPath << " " <<
				emissionMapPath << " " <<
				reflectionMapPath << " " <<
				normalMapPath << " " <<
				modelSize.x << " " <<
				modelSize.y << " " <<
				modelSize.z << " " <<
				isFaceCulled << " " <<
				isTransparent << " " <<
				reflectionType << " " <<
				isSpecular << " " <<
				specularFactor << " " <<
				specularIntensity << " " <<
				lightness << " " <<
				color.r << " " <<
				color.g << " " <<
				color.b << " " <<
				uvRepeat << " " <<
				lodEntityID << " " <<
				isInstanced << " " <<
				isBright;

			// Add space
			if (!aabbNames.empty())
			{
				file << " ";
			}

			// Write AABB data
			for (size_t i = 0; i < aabbNames.size(); i++)
			{
				file <<
					aabbNames[i] << " " <<
					aabbPositions[i].x << " " <<
					aabbPositions[i].y << " " <<
					aabbPositions[i].z << " " <<
					aabbSizes[i].x << " " <<
					aabbSizes[i].y << " " <<
					aabbSizes[i].z;

				// Add space
				if (i != (aabbNames.size() - 1))
				{
					file << " ";
				}
			}

			// Add newline
			file << std::endl;
		}
		else
		{
			file << modelID << " ? ? ? ? ? 0.0 0.0 0.0 0 0 0 0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 ? 0\n";
		}
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Model data from project \"" + _currentProjectID + "\" saved!");

	// Return
	return true;
}