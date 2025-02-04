#include "water_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const vector<string> WaterEditor::getImagePathsFromFile() const
{
	if(!Tools::isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Tools::isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "domain\\water.fe3d");

	auto file = ifstream(filePath);

	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `domain\\water.fe3d` does not exist");

		return {};
	}

	vector<string> imagePaths = {};
	string line = "";

	while(getline(file, line))
	{
		string waterId;
		string dudvMapPath;
		string normalMapPath;
		string heightMapPath;

		auto iss = istringstream(line);

		iss
			>> waterId
			>> dudvMapPath
			>> normalMapPath
			>> heightMapPath;

		dudvMapPath = (dudvMapPath == "?" ? "" : dudvMapPath);
		normalMapPath = (normalMapPath == "?" ? "" : normalMapPath);
		heightMapPath = (heightMapPath == "?" ? "" : heightMapPath);

		replace(dudvMapPath.begin(), dudvMapPath.end(), '?', ' ');
		replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
		replace(heightMapPath.begin(), heightMapPath.end(), '?', ' ');

		if(!dudvMapPath.empty())
		{
			if(!Tools::isApplicationExported())
			{
				dudvMapPath = ("projects\\" + getCurrentProjectId() + "\\" + dudvMapPath);
			}

			imagePaths.push_back(dudvMapPath);
		}

		if(!normalMapPath.empty())
		{
			if(!Tools::isApplicationExported())
			{
				normalMapPath = ("projects\\" + getCurrentProjectId() + "\\" + normalMapPath);
			}

			imagePaths.push_back(normalMapPath);
		}

		if(!heightMapPath.empty())
		{
			if(!Tools::isApplicationExported())
			{
				heightMapPath = ("projects\\" + getCurrentProjectId() + "\\" + heightMapPath);
			}

			imagePaths.push_back(heightMapPath);
		}
	}

	file.close();

	return imagePaths;
}

const bool WaterEditor::loadWatersFromFile()
{
	if(!Tools::isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Tools::isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "domain\\water.fe3d");

	auto file = ifstream(filePath);

	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `domain\\water.fe3d` does not exist");

		return false;
	}

	string line = "";

	while(getline(file, line))
	{
		string waterId;
		string dudvMapPath;
		string normalMapPath;
		string heightMapPath;
		fvec3 color;
		fvec2 rippleSpeed;
		fvec2 waveSpeed;
		float size;
		float waveHeight;
		float specularShininess;
		float specularIntensity;
		float maxDepth;
		float lightness;
		float distortionSize;
		float distortionFactor;
		float captureOffset;
		int textureRepeat;
		bool isSpecular;
		bool isReflective;
		bool isRefractive;
		bool isEdged;
		bool isCapturingSky;
		bool isCapturingTerrain;
		bool isCapturingModels;
		bool isCapturingQuad3ds;
		bool isCapturingText3ds;
		bool isCapturingAabbs;

		auto iss = istringstream(line);

		iss
			>> waterId
			>> dudvMapPath
			>> normalMapPath
			>> heightMapPath
			>> isSpecular
			>> isReflective
			>> isRefractive
			>> color.r
			>> color.g
			>> color.b
			>> size
			>> textureRepeat
			>> waveHeight
			>> rippleSpeed.x
			>> rippleSpeed.y
			>> waveSpeed.x
			>> waveSpeed.y
			>> isEdged
			>> specularShininess
			>> specularIntensity
			>> maxDepth
			>> lightness
			>> distortionSize
			>> distortionFactor
			>> captureOffset
			>> isCapturingSky
			>> isCapturingTerrain
			>> isCapturingModels
			>> isCapturingQuad3ds
			>> isCapturingText3ds
			>> isCapturingAabbs;

		dudvMapPath = (dudvMapPath == "?" ? "" : dudvMapPath);
		normalMapPath = (normalMapPath == "?" ? "" : normalMapPath);
		heightMapPath = (heightMapPath == "?" ? "" : heightMapPath);

		replace(dudvMapPath.begin(), dudvMapPath.end(), '?', ' ');
		replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
		replace(heightMapPath.begin(), heightMapPath.end(), '?', ' ');

		_fe3d->water_create(waterId);
		_fe3d->water_setSize(waterId, size);
		_fe3d->water_setSpecular(waterId, isSpecular);
		_fe3d->water_setReflective(waterId, isReflective);
		_fe3d->water_setRefractive(waterId, isRefractive);
		_fe3d->water_setWaveHeight(waterId, waveHeight);
		_fe3d->water_setSpecularShininess(waterId, specularShininess);
		_fe3d->water_setSpecularIntensity(waterId, specularIntensity);
		_fe3d->water_setEdged(waterId, isEdged);
		_fe3d->water_setColor(waterId, color);
		_fe3d->water_setTextureRepeat(waterId, textureRepeat);
		_fe3d->water_setRippleSpeed(waterId, rippleSpeed);
		_fe3d->water_setWaveSpeed(waterId, waveSpeed);
		_fe3d->water_setMaxDepth(waterId, maxDepth);
		_fe3d->water_setLightness(waterId, lightness);
		_fe3d->water_setDistortionSize(waterId, distortionSize);
		_fe3d->water_setDistortionFactor(waterId, distortionFactor);
		_fe3d->water_setCaptureOffset(waterId, captureOffset);
		_fe3d->water_setCapturingSky(waterId, isCapturingSky);
		_fe3d->water_setCapturingTerrain(waterId, isCapturingTerrain);
		_fe3d->water_setCapturingModels(waterId, isCapturingModels);
		_fe3d->water_setCapturingQuad3ds(waterId, isCapturingQuad3ds);
		_fe3d->water_setCapturingText3ds(waterId, isCapturingText3ds);
		_fe3d->water_setCapturingAabbs(waterId, isCapturingAabbs);

		if(!dudvMapPath.empty())
		{
			if(!Tools::isApplicationExported())
			{
				dudvMapPath = ("projects\\" + getCurrentProjectId() + "\\" + dudvMapPath);
			}

			_fe3d->water_setDudvMap(waterId, dudvMapPath);
		}

		if(!normalMapPath.empty())
		{
			if(!Tools::isApplicationExported())
			{
				normalMapPath = ("projects\\" + getCurrentProjectId() + "\\" + normalMapPath);
			}

			_fe3d->water_setNormalMap(waterId, normalMapPath);
		}

		if(!heightMapPath.empty())
		{
			if(!Tools::isApplicationExported())
			{
				heightMapPath = ("projects\\" + getCurrentProjectId() + "\\" + heightMapPath);
			}

			_fe3d->water_setHeightMap(waterId, heightMapPath);
		}

		_loadedWaterIds.push_back(waterId);

		sort(_loadedWaterIds.begin(), _loadedWaterIds.end());
	}

	file.close();

	Logger::throwInfo("Water editor data loaded");

	return true;
}