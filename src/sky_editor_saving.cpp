#include "sky_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool SkyEditor::saveSkiesToFile() const
{
	if(!isLoaded())
	{
		return false;
	}

	if(getCurrentProjectId().empty())
	{
		abort();
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + "projects\\" + getCurrentProjectId() + "\\domain\\sky.fe3d");

	auto file = ofstream(filePath);

	for(const auto & skyId : _loadedSkyIds)
	{
		const auto rotation = _fe3d->sky_getRotation(skyId);
		const auto lightness = _fe3d->sky_getLightness(skyId);
		const auto color = _fe3d->sky_getColor(skyId);
		const auto rotationOrder = static_cast<int>(_fe3d->sky_getRotationOrder(skyId));

		auto cubeMapPaths = _fe3d->sky_getCubeMapPaths(skyId);

		for(auto & cubeMapPath : cubeMapPaths)
		{
			if(!cubeMapPath.empty())
			{
				cubeMapPath = cubeMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size());
			}

			cubeMapPath = (cubeMapPath.empty()) ? "?" : cubeMapPath;

			replace(cubeMapPath.begin(), cubeMapPath.end(), ' ', '?');
		}

		file
			<< skyId;

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
			<< endl;
	}

	file.close();

	Logger::throwInfo("Sky editor data saved");

	return true;
}