#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::terrainEntity_add(const string& ID, const string& heightMapPath)
{
	_core->_terrainEntityManager.addTerrainEntity(ID);
	terrainEntity_setHeightMap(ID, heightMapPath);
}

void FabiEngine3D::terrainEntity_setHeightMap(const string& ID, const string& texturePath)
{
	auto pixelValues = _core->_textureLoader.getBitmapPixels(texturePath);

	// Check if heightMap loading went well
	if (pixelValues != nullptr)
	{
		_core->_terrainEntityManager.getEntity(ID)->setHeightMapPath(texturePath);
		_core->_terrainEntityManager.getEntity(ID)->setPixelValues(*pixelValues);
		_core->_terrainEntityManager.getEntity(ID)->setSize(static_cast<float>(sqrt(pixelValues->size())));
		_core->_terrainEntityManager.generateMesh(ID);
	}
}

void FabiEngine3D::terrainEntity_deleteAll()
{
	// For every terrain entity
	for (const auto& [keyID, entity] : _core->_terrainEntityManager.getEntities())
	{
		terrainEntity_delete(entity->getID());
	}

	// Unselect terrain
	_core->_terrainEntityManager.selectTerrain("");
}

void FabiEngine3D::terrainEntity_delete(const string& ID)
{
	// Unselect terrain if selected
	if (ID == terrainEntity_getSelectedID())
	{
		_core->_terrainEntityManager.selectTerrain("");
	}

	_core->_terrainEntityManager.deleteEntity(ID);
}

void FabiEngine3D::terrainEntity_setVisible(const string& ID, bool isVisible)
{
	_core->_terrainEntityManager.getEntity(ID)->setVisible(isVisible);
}

const bool FabiEngine3D::terrainEntity_isExisting(const string& ID)
{
	return _core->_terrainEntityManager.isExisting(ID);
}

const bool FabiEngine3D::terrainEntity_isVisible(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->isVisible();
}

const bool FabiEngine3D::terrainEntity_isSpecularLighted(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->isSpecularLighted();
}

const float FabiEngine3D::terrainEntity_getSize(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getSize();
}

const float FabiEngine3D::terrainEntity_getMaxHeight(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getMaxHeight();
}

const float FabiEngine3D::terrainEntity_getUvRepeat(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getUvRepeat();
}

const bool FabiEngine3D::terrainEntity_isInside(const string& ID, float x, float z)
{
	return _core->_terrainEntityManager.isInside(ID, x, z);
}

const bool FabiEngine3D::terrainEntity_hasBlendMap(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->hasBlendMap();
}

const bool FabiEngine3D::terrainEntity_hasDiffuseMap(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->hasDiffuseMap();
}

const bool FabiEngine3D::terrainEntity_hasDiffuseMapR(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->hasDiffuseMapR();
}

const bool FabiEngine3D::terrainEntity_hasDiffuseMapG(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->hasDiffuseMapG();
}

const bool FabiEngine3D::terrainEntity_hasDiffuseMapB(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->hasDiffuseMapB();
}

const bool FabiEngine3D::terrainEntity_hasNormalMap(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->hasNormalMap();
}

const bool FabiEngine3D::terrainEntity_hasNormalMapR(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->hasNormalMapR();
}

const bool FabiEngine3D::terrainEntity_hasNormalMapG(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->hasNormalMapG();
}

const bool FabiEngine3D::terrainEntity_hasNormalMapB(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->hasNormalMapB();
}

const float FabiEngine3D::terrainEntity_getPixelHeight(const string& ID, float x, float z)
{
	return _core->_terrainEntityManager.getPixelHeight(ID, x, z);
}

const float FabiEngine3D::terrainEntity_getSpecularLightingFactor(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getSpecularLightingFactor();
}

const float FabiEngine3D::terrainEntity_getSpecularLightingIntensity(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getSpecularLightingIntensity();
}

const string FabiEngine3D::terrainEntity_getSelectedID()
{
	if (_core->_terrainEntityManager.getSelectedTerrain() != nullptr)
	{
		return _core->_terrainEntityManager.getSelectedTerrain()->getID();
	}
	else
	{
		return "";
	}
}

const vector<string> FabiEngine3D::terrainEntity_getAllIDs()
{
	vector<string> IDs;

	for (const auto& [keyID, entity] : _core->_terrainEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const string& FabiEngine3D::terrainEntity_getDiffuseMapPath(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getDiffuseMapPath();
}

const string& FabiEngine3D::terrainEntity_getNormalMapPath(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getNormalMapPath();
}

const string& FabiEngine3D::terrainEntity_getBlendMapPath(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getBlendMapPath();
}

const string& FabiEngine3D::terrainEntity_getDiffuseMapPathR(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getDiffuseMapPathR();
}

const string& FabiEngine3D::terrainEntity_getDiffuseMapPathG(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getDiffuseMapPathG();
}

const string& FabiEngine3D::terrainEntity_getDiffuseMapPathB(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getDiffuseMapPathB();
}

const string& FabiEngine3D::terrainEntity_getNormalMapPathR(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getNormalMapPathR();
}

const string& FabiEngine3D::terrainEntity_getNormalMapPathG(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getNormalMapPathG();
}

const string& FabiEngine3D::terrainEntity_getNormalMapPathB(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getNormalMapPathB();
}

const float FabiEngine3D::terrainEntity_getBlendRepeatR(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getBlendRepeatR();
}

const float FabiEngine3D::terrainEntity_getBlendRepeatG(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getBlendRepeatG();
}

const float FabiEngine3D::terrainEntity_getBlendRepeatB(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getBlendRepeatB();
}

const float FabiEngine3D::terrainEntity_getLightness(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getLightness();
}

const string& FabiEngine3D::terrainEntity_getHeightMapPath(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getHeightMapPath();
}

void FabiEngine3D::terrainEntity_select(const string& ID)
{
	_core->_terrainEntityManager.selectTerrain(ID);
}

void FabiEngine3D::terrainEntity_setMaxHeight(const string& ID, float height)
{
	_core->_terrainEntityManager.getEntity(ID)->setMaxHeight(height);

	// Check if height map is loaded
	if (!_core->_terrainEntityManager.getEntity(ID)->getHeightMapPath().empty())
	{	
		// Generate mesh again
		_core->_terrainEntityManager.generateMesh(ID);
	}
}

void FabiEngine3D::terrainEntity_setUvRepeat(const string& ID, float repeat)
{
	_core->_terrainEntityManager.getEntity(ID)->setUvRepeat(repeat);

	// Check if height map is loaded
	if (!_core->_terrainEntityManager.getEntity(ID)->getHeightMapPath().empty())
	{
		// Generate mesh again
		_core->_terrainEntityManager.generateMesh(ID);
	}
}

void FabiEngine3D::terrainEntity_setDiffuseMap(const string& ID, const string& texturePath)
{
	if (texturePath.empty())
	{
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMap(0);
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapPath("");
	}
	else
	{
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMap(_core->_textureLoader.getTexture2D(texturePath, true, true));
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapPath(texturePath);
	}
}

void FabiEngine3D::terrainEntity_setNormalMap(const string& ID, const string& texturePath)
{
	if (texturePath.empty())
	{
		_core->_terrainEntityManager.getEntity(ID)->setNormalMap(0);
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapPath("");
	}
	else
	{
		_core->_terrainEntityManager.getEntity(ID)->setNormalMap(_core->_textureLoader.getTexture2D(texturePath, true, true));
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapPath(texturePath);
	}
}

void FabiEngine3D::terrainEntity_setBlendMap(const string& ID, const string& texturePath)
{
	if (texturePath.empty())
	{
		_core->_terrainEntityManager.getEntity(ID)->setBlendMap(0);
		_core->_terrainEntityManager.getEntity(ID)->setBlendMapPath("");
	}
	else
	{
		_core->_terrainEntityManager.getEntity(ID)->setBlendMap(_core->_textureLoader.getTexture2D(texturePath, true, true));
		_core->_terrainEntityManager.getEntity(ID)->setBlendMapPath(texturePath);
	}
}

void FabiEngine3D::terrainEntity_setDiffuseMapR(const string& ID, const string& texturePath)
{
	if (texturePath.empty())
	{
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapR(0);
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapPathR("");
	}
	else
	{
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapR(_core->_textureLoader.getTexture2D(texturePath, true, true));
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapPathR(texturePath);
	}
}

void FabiEngine3D::terrainEntity_setDiffuseMapG(const string& ID, const string& texturePath)
{
	if (texturePath.empty())
	{
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapG(0);
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapPathG("");
	}
	else
	{
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapG(_core->_textureLoader.getTexture2D(texturePath, true, true));
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapPathG(texturePath);
	}
}

void FabiEngine3D::terrainEntity_setDiffuseMapB(const string& ID, const string& texturePath)
{
	if (texturePath.empty())
	{
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapB(0);
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapPathB("");
	}
	else
	{
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapB(_core->_textureLoader.getTexture2D(texturePath, true, true));
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapPathB(texturePath);
	}
}

void FabiEngine3D::terrainEntity_setNormalMapR(const string& ID, const string& texturePath)
{
	if (texturePath.empty())
	{
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapR(0);
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapPathR("");
	}
	else
	{
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapR(_core->_textureLoader.getTexture2D(texturePath, true, true));
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapPathR(texturePath);
	}
}

void FabiEngine3D::terrainEntity_setNormalMapG(const string& ID, const string& texturePath)
{
	if (texturePath.empty())
	{
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapG(0);
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapPathG("");
	}
	else
	{
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapG(_core->_textureLoader.getTexture2D(texturePath, true, true));
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapPathG(texturePath);
	}
}

void FabiEngine3D::terrainEntity_setNormalMapB(const string& ID, const string& texturePath)
{
	if (texturePath.empty())
	{
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapB(0);
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapPathB("");
	}
	else
	{
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapB(_core->_textureLoader.getTexture2D(texturePath, true, true));
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapPathB(texturePath);
	}
}

void FabiEngine3D::terrainEntity_setBlendRepeatR(const string& ID, float repeat)
{
	_core->_terrainEntityManager.getEntity(ID)->setBlendRepeatR(repeat);
}

void FabiEngine3D::terrainEntity_setBlendRepeatG(const string& ID, float repeat)
{
	_core->_terrainEntityManager.getEntity(ID)->setBlendRepeatG(repeat);
}

void FabiEngine3D::terrainEntity_setBlendRepeatB(const string& ID, float repeat)
{
	_core->_terrainEntityManager.getEntity(ID)->setBlendRepeatB(repeat);
}

void FabiEngine3D::terrainEntity_setSpecularLightingFactor(const string& ID, float factor)
{
	_core->_terrainEntityManager.getEntity(ID)->setSpecularLightingFactor(factor);
}

void FabiEngine3D::terrainEntity_setSpecularLightingIntensity(const string& ID, float intensity)
{
	_core->_terrainEntityManager.getEntity(ID)->setSpecularLightingIntensity(intensity);
}

void FabiEngine3D::terrainEntity_setLightness(const string& ID, float lightness)
{
	_core->_terrainEntityManager.getEntity(ID)->setLightness(lightness);
}

void FabiEngine3D::terrainEntity_setSpecularLighted(const string& ID, bool enabled)
{
	_core->_terrainEntityManager.getEntity(ID)->setSpecularLighted(enabled);
}