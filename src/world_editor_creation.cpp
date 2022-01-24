#include "world_editor.hpp"
#include "logger.hpp"

void WorldEditor::copyTemplateModel(const string& newId, const string& templateId, const fvec3& position)
{
	_copyTemplateModel(newId, templateId, position, true);
}

void WorldEditor::copyTemplateQuad3d(const string& newId, const string& templateId, const fvec3& position)
{
	_copyTemplateQuad3d(newId, templateId, position, true);
}

void WorldEditor::copyTemplateText3d(const string& newId, const string& templateId, const fvec3& position)
{
	_copyTemplateText3d(newId, templateId, position, true);
}

void WorldEditor::copyTemplateSound(const string& newId, const string& templateId, const fvec3& position)
{
	_copyTemplateSound(newId, templateId, position, true);
}

const bool WorldEditor::_copyTemplateSky(const string& newId, const string& templateId)
{
	if(_fe3d->sky_isExisting(newId))
	{
		Logger::throwWarning("World sky with id \"" + newId + "\" already exists!");
		return false;
	}
	if(!_fe3d->sky_isExisting(templateId))
	{
		Logger::throwWarning("Editor sky of world sky with id \"" + newId + "\" not existing anymore!");
		return false;
	}

	_fe3d->sky_create(newId);
	_fe3d->sky_setCubeMaps(newId, _fe3d->sky_getCubeMapPaths(templateId));
	_fe3d->sky_setLightness(newId, _fe3d->sky_getLightness(templateId));
	_fe3d->sky_setRotation(newId, _fe3d->sky_getRotation(templateId));
	_fe3d->sky_setColor(newId, _fe3d->sky_getColor(templateId));
	_fe3d->sky_select(newId);

	_loadedSkyId = newId;

	return true;
}

const bool WorldEditor::_copyTemplateTerrain(const string& newId, const string& templateId)
{
	if(_fe3d->terrain_isExisting(newId))
	{
		Logger::throwWarning("World terrain with id \"" + newId + "\" already exists!");
		return false;
	}
	if(!_fe3d->terrain_isExisting(templateId))
	{
		Logger::throwWarning("Editor terrain of world terrain with id \"" + newId + "\" not existing anymore!");
		return false;
	}

	if(_fe3d->terrain_isExisting(newId))
	{
		_fe3d->terrain_delete(newId);
	}

	_fe3d->terrain_create(newId, _fe3d->terrain_getHeightMapPath(templateId));
	_fe3d->terrain_select(newId);

	_fe3d->terrain_setMaxHeight(newId, _fe3d->terrain_getMaxHeight(templateId));
	_fe3d->terrain_setTextureRepeat(newId, _fe3d->terrain_getTextureRepeat(templateId));
	_fe3d->terrain_setLightness(newId, _fe3d->terrain_getLightness(templateId));
	_fe3d->terrain_setRedTextureRepeat(newId, _fe3d->terrain_getRedTextureRepeat(templateId));
	_fe3d->terrain_setGreenTextureRepeat(newId, _fe3d->terrain_getGreenTextureRepeat(templateId));
	_fe3d->terrain_setBlueTextureRepeat(newId, _fe3d->terrain_getBlueTextureRepeat(templateId));
	_fe3d->terrain_setSpecular(newId, _fe3d->terrain_isSpecular(templateId));
	_fe3d->terrain_setSpecularShininess(newId, _fe3d->terrain_getSpecularShininess(templateId));
	_fe3d->terrain_setSpecularIntensity(newId, _fe3d->terrain_getSpecularIntensity(templateId));

	if(_fe3d->terrain_hasDiffuseMap(templateId))
	{
		_fe3d->terrain_setDiffuseMap(newId, _fe3d->terrain_getDiffuseMapPath(templateId));
	}

	if(_fe3d->terrain_hasNormalMap(templateId))
	{
		_fe3d->terrain_setNormalMap(newId, _fe3d->terrain_getNormalMapPath(templateId));
	}

	if(_fe3d->terrain_hasRedNormalMap(templateId))
	{
		_fe3d->terrain_setRedNormalMap(newId, _fe3d->terrain_getRedNormalMapPath(templateId));
	}

	if(_fe3d->terrain_hasGreenNormalMap(templateId))
	{
		_fe3d->terrain_setGreenNormalMap(newId, _fe3d->terrain_getGreenNormalMapPath(templateId));
	}

	if(_fe3d->terrain_hasBlueNormalMap(templateId))
	{
		_fe3d->terrain_setBlueNormalMap(newId, _fe3d->terrain_getBlueNormalMapPath(templateId));
	}

	if(_fe3d->terrain_hasBlendMap(templateId))
	{
		_fe3d->terrain_setBlendMap(newId, _fe3d->terrain_getBlendMapPath(templateId));
	}

	if(_fe3d->terrain_hasRedDiffuseMap(templateId))
	{
		_fe3d->terrain_setRedDiffuseMap(newId, _fe3d->terrain_getRedDiffuseMapPath(templateId));
	}

	if(_fe3d->terrain_hasGreenDiffuseMap(templateId))
	{
		_fe3d->terrain_setGreenDiffuseMap(newId, _fe3d->terrain_getGreenDiffuseMapPath(templateId));
	}

	if(_fe3d->terrain_hasBlueDiffuseMap(templateId))
	{
		_fe3d->terrain_setBlueDiffuseMap(newId, _fe3d->terrain_getBlueDiffuseMapPath(templateId));
	}

	_loadedTerrainId = newId;

	return true;
}

const bool WorldEditor::_copyTemplateWater(const string& newId, const string& templateId)
{
	if(_fe3d->water_isExisting(newId))
	{
		Logger::throwWarning("World water with id \"" + newId + "\" already exists!");
		return false;
	}
	if(!_fe3d->water_isExisting(templateId))
	{
		Logger::throwWarning("Editor water of world water with id \"" + newId + "\" not existing anymore!");
		return false;
	}

	if(_fe3d->water_isExisting(newId))
	{
		_fe3d->water_delete(newId);
	}

	_fe3d->water_create(newId);
	_fe3d->water_select(newId);

	_fe3d->water_setHeight(newId, _fe3d->water_getHeight(templateId));
	_fe3d->water_setSize(newId, _fe3d->water_getSize(templateId));
	_fe3d->water_setSpecular(newId, _fe3d->water_isSpecular(templateId));
	_fe3d->water_setReflective(newId, _fe3d->water_isReflective(templateId));
	_fe3d->water_setRefractive(newId, _fe3d->water_isRefractive(templateId));
	_fe3d->water_setWaveHeight(newId, _fe3d->water_getWaveHeight(templateId));
	_fe3d->water_setQuality(newId, _fe3d->water_getQuality(templateId));
	_fe3d->water_setSpecularShininess(newId, _fe3d->water_getSpecularShininess(templateId));
	_fe3d->water_setSpecularIntensity(newId, _fe3d->water_getSpecularIntensity(templateId));
	_fe3d->water_setOpacity(newId, _fe3d->water_getOpacity(templateId));
	_fe3d->water_setColor(newId, _fe3d->water_getColor(templateId));
	_fe3d->water_setTextureRepeat(newId, _fe3d->water_getTextureRepeat(templateId));
	_fe3d->water_setSpeed(newId, _fe3d->water_getSpeed(templateId));

	if(_fe3d->water_hasDudvMap(templateId))
	{
		_fe3d->water_setDudvMap(newId, _fe3d->water_getDudvMapPath(templateId));
	}

	if(_fe3d->water_hasNormalMap(templateId))
	{
		_fe3d->water_setNormalMap(newId, _fe3d->water_getNormalMapPath(templateId));
	}

	if(_fe3d->water_hasDisplacementMap(templateId))
	{
		_fe3d->water_setDisplacementMap(newId, _fe3d->water_getDisplacementMapPath(templateId));
	}

	_loadedWaterId = newId;

	return true;
}

const bool WorldEditor::_copyTemplateModel(const string& newId, const string& templateId, const fvec3& position, bool isFromOutside)
{
	if(_fe3d->model_isExisting(newId))
	{
		Logger::throwWarning("Model with id \"" + newId + "\" already exists!");
		return false;
	}
	if(!_fe3d->model_isExisting(templateId))
	{
		Logger::throwWarning("Editor model of model with id \"" + newId + "\" not existing anymore!");
		return false;
	}

	_fe3d->model_create(newId, _fe3d->model_getMeshPath(templateId));

	_fe3d->model_setBasePosition(newId, position);
	_fe3d->model_setBaseSize(newId, _fe3d->model_getBaseSize(templateId));
	_fe3d->model_setLevelOfDetailSize(newId, _fe3d->model_getBaseSize(templateId));
	_fe3d->model_setFrozen(newId, _fe3d->model_isFrozen(templateId));
	_fe3d->model_setLevelOfDetailEntityId(newId, _fe3d->model_getLevelOfDetailEntityId(templateId));
	_fe3d->model_setRotationOrder(newId, _fe3d->model_getRotationOrder(templateId));

	for(const auto& partId : _fe3d->model_getPartIds(templateId))
	{
		if(_fe3d->model_hasDiffuseMap(templateId, partId))
		{
			_fe3d->model_setDiffuseMap(newId, partId, _fe3d->model_getDiffuseMapPath(templateId, partId));
		}

		if(_fe3d->model_hasEmissionMap(templateId, partId))
		{
			_fe3d->model_setEmissionMap(newId, partId, _fe3d->model_getEmissionMapPath(templateId, partId));
		}

		if(_fe3d->model_hasSpecularMap(templateId, partId))
		{
			_fe3d->model_setSpecularMap(newId, partId, _fe3d->model_getSpecularMapPath(templateId, partId));
		}

		if(_fe3d->model_hasReflectionMap(templateId, partId))
		{
			_fe3d->model_setReflectionMap(newId, partId, _fe3d->model_getReflectionMapPath(templateId, partId));
		}

		if(_fe3d->model_hasNormalMap(templateId, partId))
		{
			_fe3d->model_setNormalMap(newId, partId, _fe3d->model_getNormalMapPath(templateId, partId));
		}

		_fe3d->model_setLightness(newId, partId, _fe3d->model_getLightness(templateId, partId));
		_fe3d->model_setSpecular(newId, partId, _fe3d->model_isSpecular(templateId, partId));
		_fe3d->model_setSpecularShininess(newId, partId, _fe3d->model_getSpecularShininess(templateId, partId));
		_fe3d->model_setSpecularIntensity(newId, partId, _fe3d->model_getSpecularIntensity(templateId, partId));
		_fe3d->model_setReflective(newId, partId, _fe3d->model_isReflective(templateId, partId));
		_fe3d->model_setReflectionType(newId, partId, _fe3d->model_getReflectionType(templateId, partId));
		_fe3d->model_setReflectivity(newId, partId, _fe3d->model_getReflectivity(templateId, partId));
		_fe3d->model_setColor(newId, partId, _fe3d->model_getColor(templateId, partId));
		_fe3d->model_setTextureRepeat(newId, partId, _fe3d->model_getTextureRepeat(templateId, partId));
		_fe3d->model_setFaceCulled(newId, partId, _fe3d->model_isFaceCulled(templateId, partId));
	}

	for(const auto& templateAabbId : _fe3d->aabb_getChildIds(templateId, AabbParentEntityType::MODEL))
	{
		const string newAabbId = (newId + "@" + templateAabbId.substr(string(templateId + "_").size()));
		_fe3d->aabb_create(newAabbId, false);
		_fe3d->aabb_setParentEntityId(newAabbId, newId);
		_fe3d->aabb_setParentEntityType(newAabbId, AabbParentEntityType::MODEL);
		_fe3d->aabb_setLocalPosition(newAabbId, _fe3d->aabb_getPosition(templateAabbId));
		_fe3d->aabb_setLocalSize(newAabbId, _fe3d->aabb_getSize(templateAabbId));
	}

	if(_isEditorLoaded)
	{
		_initialModelPosition.insert(make_pair(newId, _fe3d->model_getBasePosition(templateId)));
		_initialModelRotation.insert(make_pair(newId, _fe3d->model_getBaseRotation(templateId)));
		_initialModelSize.insert(make_pair(newId, _fe3d->model_getBaseSize(templateId)));
	}

	if(isFromOutside)
	{
		_outsideLoadedModelIds.insert(make_pair(newId, templateId));
	}
	else
	{
		_loadedModelIds.insert(make_pair(newId, templateId));
	}

	return true;
}

const bool WorldEditor::_copyTemplateQuad3d(const string& newId, const string& templateId, const fvec3& position, bool isFromOutside)
{
	if(_fe3d->quad3d_isExisting(newId))
	{
		Logger::throwWarning("Quad3d with id \"" + newId + "\" already exists!");
		return false;
	}
	if(!_fe3d->quad3d_isExisting(templateId))
	{
		Logger::throwWarning("Editor quad3d of quad3d with id \"" + newId + "\" not existing anymore!");
		return false;
	}

	_fe3d->quad3d_create(newId, false);

	_fe3d->aabb_create(newId, false);
	_fe3d->aabb_setParentEntityId(newId, newId);
	_fe3d->aabb_setParentEntityType(newId, AabbParentEntityType::QUAD3D);

	if(_fe3d->quad3d_hasDiffuseMap(templateId))
	{
		_fe3d->quad3d_setDiffuseMap(newId, _fe3d->quad3d_getDiffuseMapPath(templateId));
	}

	if(_fe3d->quad3d_hasEmissionMap(templateId))
	{
		_fe3d->quad3d_setEmissionMap(newId, _fe3d->quad3d_getEmissionMapPath(templateId));
	}

	_fe3d->quad3d_setPosition(newId, position);
	_fe3d->quad3d_setSize(newId, _fe3d->quad3d_getSize(templateId));
	_fe3d->quad3d_setFacingCameraX(newId, _fe3d->quad3d_isFacingCameraX(templateId));
	_fe3d->quad3d_setFacingCameraY(newId, _fe3d->quad3d_isFacingCameraY(templateId));
	_fe3d->quad3d_setColor(newId, _fe3d->quad3d_getColor(templateId));
	_fe3d->quad3d_setShadowed(newId, _fe3d->quad3d_isShadowed(templateId));
	_fe3d->quad3d_setReflected(newId, _fe3d->quad3d_isReflected(templateId));
	_fe3d->quad3d_setLightness(newId, _fe3d->quad3d_getLightness(templateId));

	if(isFromOutside)
	{
		_outsideLoadedQuadIds.insert(make_pair(newId, templateId));
	}
	else
	{
		_loadedQuadIds.insert(make_pair(newId, templateId));
	}

	return true;
}

const bool WorldEditor::_copyTemplateText3d(const string& newId, const string& templateId, const fvec3& position, bool isFromOutside)
{
	if(_fe3d->text3d_isExisting(newId))
	{
		Logger::throwWarning("Text3d with id \"" + newId + "\" already exists!");
		return false;
	}
	if(!_fe3d->text3d_isExisting(templateId))
	{
		Logger::throwWarning("Editor text3d of text3d with id \"" + newId + "\" not existing anymore!");
		return false;
	}

	_fe3d->text3d_create(newId, _fe3d->text3d_getFontMapPath(templateId), false);

	_fe3d->aabb_create(newId, false);
	_fe3d->aabb_setParentEntityId(newId, newId);
	_fe3d->aabb_setParentEntityType(newId, AabbParentEntityType::TEXT3D);

	_fe3d->text3d_setPosition(newId, position);
	_fe3d->text3d_setSize(newId, _fe3d->text3d_getSize(templateId));
	_fe3d->text3d_setFacingCameraX(newId, _fe3d->text3d_isFacingCameraX(templateId));
	_fe3d->text3d_setFacingCameraY(newId, _fe3d->text3d_isFacingCameraY(templateId));
	_fe3d->text3d_setColor(newId, _fe3d->text3d_getColor(templateId));
	_fe3d->text3d_setShadowed(newId, _fe3d->text3d_isShadowed(templateId));
	_fe3d->text3d_setReflected(newId, _fe3d->text3d_isReflected(templateId));
	_fe3d->text3d_setLightness(newId, _fe3d->text3d_getLightness(templateId));
	_fe3d->text3d_setContent(newId, _fe3d->text3d_getContent(templateId));

	if(isFromOutside)
	{
		_outsideLoadedTextIds.insert(make_pair(newId, templateId));
	}
	else
	{
		_loadedTextIds.insert(make_pair(newId, templateId));
	}

	return true;
}

const bool WorldEditor::_copyTemplateSound(const string& newId, const string& templateId, const fvec3& position, bool isFromOutside)
{
	if(_fe3d->sound3d_isExisting(newId))
	{
		Logger::throwWarning("sound3D with id \"" + newId + "\" already exists!");
		return false;
	}
	if(!_fe3d->sound2d_isExisting(templateId))
	{
		Logger::throwWarning("sound2D with id \"" + newId + "\" not existing anymore!");
		return false;
	}

	_fe3d->sound3d_create(newId, _fe3d->sound2d_getAudioPath(templateId));
	_fe3d->sound3d_setPosition(newId, position);

	if(isFromOutside)
	{
		_outsideLoadedSoundIds.insert(make_pair(newId, templateId));
	}
	else
	{
		_loadedSoundIds.insert(make_pair(newId, templateId));
	}

	return true;
}