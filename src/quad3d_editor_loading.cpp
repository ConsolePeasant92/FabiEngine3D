#include "quad3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const vector<string> Quad3dEditor::getImagePathsFromFile() const
{
	if(!Tools::isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Tools::isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "domain\\quad3d.fe3d");

	auto file = ifstream(filePath);

	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `domain\\quad3d.fe3d` does not exist");

		return {};
	}

	vector<string> imagePaths = {};
	string line = "";

	while(getline(file, line))
	{
		string lineType;

		auto iss = istringstream(line);

		iss >> lineType;

		if(lineType == "QUAD3D")
		{
			string quad3dId;
			string diffuseMapPath;
			string emissionMapPath;

			iss
				>> quad3dId
				>> diffuseMapPath
				>> emissionMapPath;

			diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
			emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;

			replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
			replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');

			if(!diffuseMapPath.empty())
			{
				if(!Tools::isApplicationExported())
				{
					diffuseMapPath = ("projects\\" + getCurrentProjectId() + "\\" + diffuseMapPath);
				}

				imagePaths.push_back(diffuseMapPath);
			}

			if(!emissionMapPath.empty())
			{
				if(!Tools::isApplicationExported())
				{
					emissionMapPath = ("projects\\" + getCurrentProjectId() + "\\" + emissionMapPath);
				}

				imagePaths.push_back(emissionMapPath);
			}
		}
	}

	file.close();

	return imagePaths;
}

const bool Quad3dEditor::loadQuad3dsFromFile()
{
	if(!Tools::isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Tools::isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "domain\\quad3d.fe3d");

	auto file = ifstream(filePath);

	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `domain\\quad3d.fe3d` does not exist");

		return false;
	}

	string line = "";

	while(getline(file, line))
	{
		string lineType;

		auto iss = istringstream(line);

		iss >> lineType;

		if(lineType == "QUAD3D")
		{
			string quad3dId;
			string diffuseMapPath;
			string emissionMapPath;
			fvec2 size;
			fvec3 color;
			float lightness;
			float opacity;
			float minAlpha;
			float emissionIntensity;
			int textureRepeat;
			int rotationOrder;
			bool isFacingCameraHorizontally;
			bool isFacingCameraVertically;
			bool isHorizontallyFlipped;
			bool isVerticallyFlipped;
			bool isReflected;
			bool isRefracted;
			bool isShadowed;
			bool isBright;

			iss
				>> quad3dId
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
				>> isRefracted
				>> isShadowed
				>> lightness
				>> textureRepeat
				>> isBright
				>> emissionIntensity
				>> opacity
				>> minAlpha
				>> rotationOrder;

			diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
			emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;

			replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
			replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');

			_fe3d->quad3d_create(quad3dId, false);
			_fe3d->quad3d_setVisible(quad3dId, false);
			_fe3d->quad3d_setSize(quad3dId, size);
			_fe3d->quad3d_setColor(quad3dId, color);
			_fe3d->quad3d_setLightness(quad3dId, lightness);
			_fe3d->quad3d_setFacingCameraHorizontally(quad3dId, isFacingCameraHorizontally);
			_fe3d->quad3d_setFacingCameraVertically(quad3dId, isFacingCameraVertically);
			_fe3d->quad3d_setHorizontallyFlipped(quad3dId, isHorizontallyFlipped);
			_fe3d->quad3d_setVerticallyFlipped(quad3dId, isVerticallyFlipped);
			_fe3d->quad3d_setShadowed(quad3dId, isShadowed);
			_fe3d->quad3d_setReflected(quad3dId, isReflected);
			_fe3d->quad3d_setRefracted(quad3dId, isRefracted);
			_fe3d->quad3d_setTextureRepeat(quad3dId, textureRepeat);
			_fe3d->quad3d_setBright(quad3dId, isBright);
			_fe3d->quad3d_setOpacity(quad3dId, opacity);
			_fe3d->quad3d_setEmissionIntensity(quad3dId, emissionIntensity);
			_fe3d->quad3d_setMinAlpha(quad3dId, minAlpha);
			_fe3d->quad3d_setRotationOrder(quad3dId, DirectionOrderType(rotationOrder));

			if(!diffuseMapPath.empty())
			{
				if(!Tools::isApplicationExported())
				{
					diffuseMapPath = ("projects\\" + getCurrentProjectId() + "\\" + diffuseMapPath);
				}

				_fe3d->quad3d_setDiffuseMap(quad3dId, diffuseMapPath);
			}

			if(!emissionMapPath.empty())
			{
				if(!Tools::isApplicationExported())
				{
					emissionMapPath = ("projects\\" + getCurrentProjectId() + "\\" + emissionMapPath);
				}

				_fe3d->quad3d_setEmissionMap(quad3dId, emissionMapPath);
			}

			_loadedQuad3dIds.push_back(quad3dId);

			sort(_loadedQuad3dIds.begin(), _loadedQuad3dIds.end());
		}
		else if(lineType == "AABB")
		{
			string quad3dId;
			string aabbId;

			iss
				>> quad3dId
				>> aabbId;

			if(!_fe3d->quad3d_isExisting(quad3dId))
			{
				continue;
			}

			_fe3d->aabb_create(aabbId, false);
			_fe3d->aabb_bindToParent(aabbId, quad3dId, AabbParentType::QUAD3D);
		}
		else
		{
			abort();
		}
	}

	file.close();

	Logger::throwInfo("Quad3D editor data loaded");

	return true;
}