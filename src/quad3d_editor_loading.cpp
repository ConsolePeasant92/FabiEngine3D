#include "quad3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const vector<string> Quad3dEditor::getImagePathsFromFile() const
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\quad3d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `quad3d.fe3d` does not exist");
		return {};
	}

	vector<string> imagePaths;
	string line;
	while(getline(file, line))
	{
		string quadId;
		string diffuseMapPath;
		string emissionMapPath;

		istringstream iss(line);

		iss
			>> quadId
			>> diffuseMapPath
			>> emissionMapPath;

		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');

		if(!diffuseMapPath.empty())
		{
			if(!Configuration::getInst().isApplicationExported())
			{
				diffuseMapPath = ("projects\\" + getCurrentProjectId() + "\\" + diffuseMapPath);
			}

			imagePaths.push_back(diffuseMapPath);
		}

		if(!emissionMapPath.empty())
		{
			if(!Configuration::getInst().isApplicationExported())
			{
				emissionMapPath = ("projects\\" + getCurrentProjectId() + "\\" + emissionMapPath);
			}

			imagePaths.push_back(emissionMapPath);
		}
	}

	file.close();

	return imagePaths;
}

const bool Quad3dEditor::loadEntitiesFromFile()
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\quad3d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `quad3d.fe3d` does not exist");

		return false;
	}

	string line;
	while(getline(file, line))
	{
		string quadId;
		string diffuseMapPath;
		string emissionMapPath;
		fvec2 size;
		fvec3 color;
		float lightness;
		float opacity;
		float minTextureAlpha;
		float emissionIntensity;
		int textureRepeat;
		int rotationOrder;
		bool isFacingCameraHorizontally;
		bool isFacingCameraVertically;
		bool isHorizontallyFlipped;
		bool isVerticallyFlipped;
		bool isReflected;
		bool isShadowed;
		bool isBright;
		bool hasAabb;

		istringstream iss(line);

		iss
			>> quadId
			>> diffuseMapPath
			>> emissionMapPath
			>> size.x
			>> size.y
			>> color.r
			>> color.g
			>> color.b
			>> isFacingCameraHorizontally
			>> isFacingCameraVertically
			>> isHorizontallyFlipped
			>> isVerticallyFlipped
			>> isReflected
			>> isShadowed
			>> lightness
			>> textureRepeat
			>> isBright
			>> emissionIntensity
			>> opacity
			>> minTextureAlpha
			>> rotationOrder
			>> hasAabb;

		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');

		_loadedEntityIds.push_back(quadId);
		sort(_loadedEntityIds.begin(), _loadedEntityIds.end());

		_fe3d->quad3d_create(quadId, false);
		_fe3d->quad3d_setVisible(quadId, false);
		_fe3d->quad3d_setSize(quadId, size);
		_fe3d->quad3d_setColor(quadId, color);
		_fe3d->quad3d_setLightness(quadId, lightness);
		_fe3d->quad3d_setFacingCameraHorizontally(quadId, isFacingCameraHorizontally);
		_fe3d->quad3d_setFacingCameraVertically(quadId, isFacingCameraVertically);
		_fe3d->quad3d_setHorizontallyFlipped(quadId, isHorizontallyFlipped);
		_fe3d->quad3d_setVerticallyFlipped(quadId, isVerticallyFlipped);
		_fe3d->quad3d_setShadowed(quadId, isShadowed);
		_fe3d->quad3d_setReflected(quadId, isReflected);
		_fe3d->quad3d_setTextureRepeat(quadId, textureRepeat);
		_fe3d->quad3d_setBright(quadId, isBright);
		_fe3d->quad3d_setOpacity(quadId, opacity);
		_fe3d->quad3d_setEmissionIntensity(quadId, emissionIntensity);
		_fe3d->quad3d_setMinTextureAlpha(quadId, minTextureAlpha);
		_fe3d->quad3d_setRotationOrder(quadId, DirectionOrderType(rotationOrder));

		if(hasAabb)
		{
			_fe3d->aabb_create(quadId, false);
			_fe3d->aabb_setParentId(quadId, quadId);
			_fe3d->aabb_setParentType(quadId, AabbParentType::QUAD3D);
		}

		if(!diffuseMapPath.empty())
		{
			if(!Configuration::getInst().isApplicationExported())
			{
				diffuseMapPath = ("projects\\" + getCurrentProjectId() + "\\" + diffuseMapPath);
			}

			_fe3d->quad3d_setDiffuseMap(quadId, diffuseMapPath);
		}

		if(!emissionMapPath.empty())
		{
			if(!Configuration::getInst().isApplicationExported())
			{
				emissionMapPath = ("projects\\" + getCurrentProjectId() + "\\" + emissionMapPath);
			}

			_fe3d->quad3d_setEmissionMap(quadId, emissionMapPath);
		}
	}

	file.close();

	Logger::throwInfo("Quad3D editor data loaded");

	return true;
}