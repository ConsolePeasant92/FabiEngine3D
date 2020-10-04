#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::billBoardEntity_add(const string& ID, vec3 color, vec3 T, vec3 R, vec2 S, bool facingCameraX, bool facingCameraY, bool visible)
{
	_core->_billboardEntityManager.addBillboardEntity(ID, color, T, R, vec3(S.x, S.y, 1.0f), facingCameraX, facingCameraY);
	_core->_billboardEntityManager.getEntity(ID)->setVisible(visible);
}

void FabiEngine3D::billBoardEntity_add(const string& ID, const string& diffuseMapPath, vec3 T, vec3 R, vec2 S, bool transparent, bool facingCameraX, bool facingCameraY, bool textureFiltering, bool visible)
{
	_core->_billboardEntityManager.addBillboardEntity(ID, diffuseMapPath, T, R, vec3(S.x, S.y, 1.0f), transparent, facingCameraX, facingCameraY, textureFiltering);
	_core->_billboardEntityManager.getEntity(ID)->setVisible(visible);
}

void FabiEngine3D::billBoardEntity_add(const string& ID, const string& text, const string& fontPath, vec3 color, vec3 T, vec3 R, vec2 S, bool facingCameraX, bool facingCameraY, bool visible)
{
	_core->_billboardEntityManager.addBillboardEntity(ID, text, fontPath, color, T, R, vec3(S.x, S.y, 1.0f), facingCameraX, facingCameraY);
	_core->_billboardEntityManager.getEntity(ID)->setVisible(visible);
}

void FabiEngine3D::billboardEntity_deleteAll()
{
	for (auto& entity : _core->_billboardEntityManager.getEntities())
	{
		billboardEntity_delete(entity->getID());
	}
}

void FabiEngine3D::billboardEntity_delete(const string& ID)
{
	// Delete AABB child entity if existing
	for (auto& entity : _core->_aabbEntityManager.getEntities())
	{
		for (auto& aabbID : aabbEntity_getBoundIDs(entity->getID(), false, true))
		{
			_core->_aabbEntityManager.deleteEntity(ID, EntityType::AABB);
		}
	}

	// Delete BILLBOARD entity
	_core->_billboardEntityManager.deleteEntity(ID, EntityType::BILLBOARD);
}

void FabiEngine3D::billboardEntity_deleteGroup(const string& ID)
{
	for (auto& entity : _core->_billboardEntityManager.getEntities()) // Loop over BILLBOARD entities
	{
		if (entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			auto subString = entity->getID().substr(0, ID.size());

			// If entity matches ID
			if (subString == ID)
			{
				billboardEntity_delete(entity->getID());
			}
		}
	}
}

void FabiEngine3D::billboardEntity_hideAll()
{
	for (auto& entity : _core->_billboardEntityManager.getEntities())
	{
		// Hide every bound AABB
		for (auto& aabbID : aabbEntity_getBoundIDs(entity->getID(), false, true))
		{
			aabbEntity_hide(aabbID);
		}

		entity->setVisible(false);
	}
}

void FabiEngine3D::billboardEntity_showAll()
{
	for (auto& entity : _core->_billboardEntityManager.getEntities())
	{
		// Show every bound AABB
		for (auto& aabbID : aabbEntity_getBoundIDs(entity->getID(), false, true))
		{
			aabbEntity_show(aabbID);
		}

		entity->setVisible(true);
	}
}

void FabiEngine3D::billboardEntity_hide(const string& ID)
{
	// Hide every bound AABB
	for (auto& aabbID : aabbEntity_getBoundIDs(ID, false, true))
	{
		aabbEntity_hide(aabbID);
	}

	_core->_billboardEntityManager.getEntity(ID)->setVisible(false);
}

void FabiEngine3D::billboardEntity_show(const string& ID)
{
	// Show every bound AABB
	for (auto& aabbID : aabbEntity_getBoundIDs(ID, false, true))
	{
		aabbEntity_show(aabbID);
	}

	_core->_billboardEntityManager.getEntity(ID)->setVisible(true);
}

bool FabiEngine3D::billboardEntity_isExisting(const string& ID)
{
	return _core->_billboardEntityManager.isExisting(ID);
}

bool FabiEngine3D::billboardEntity_isVisible(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isVisible();
}

void FabiEngine3D::billboardEntity_move(const string& ID, vec3 factor)
{
	_core->_billboardEntityManager.getEntity(ID)->translate(factor);
}

void FabiEngine3D::billboardEntity_rotate(const string& ID, vec3 factor)
{
	_core->_billboardEntityManager.getEntity(ID)->rotate(factor);
}

void FabiEngine3D::billboardEntity_scale(const string& ID, vec3 factor)
{
	_core->_billboardEntityManager.getEntity(ID)->scale(factor);
}

void FabiEngine3D::billboardEntity_setPosition(const string& ID, vec3 position)
{
	_core->_billboardEntityManager.getEntity(ID)->setTranslation(position);
}

void FabiEngine3D::billboardEntity_setRotation(const string& ID, vec3 rotation)
{
	_core->_billboardEntityManager.getEntity(ID)->setRotation(rotation);
}

void FabiEngine3D::billboardEntity_setSize(const string& ID, vec2 size)
{
	_core->_billboardEntityManager.getEntity(ID)->setScaling(vec3(size.x, size.y, 1.0f));
}

void FabiEngine3D::billboardEntity_setColor(const string& ID, vec3 color)
{
	_core->_billboardEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::billboardEntity_setDiffuseMap(const string& ID, const string& texturePath, bool textureFiltering)
{
	_core->_billboardEntityManager.getEntity(ID)->setDiffuseMap(_core->_texLoader.getTexture(texturePath, textureFiltering, textureFiltering));
	_core->_billboardEntityManager.getEntity(ID)->setDiffuseMapPath(texturePath);
}

void FabiEngine3D::billboardEntity_setTransparent(const string& ID, bool enabled)
{
	_core->_billboardEntityManager.getEntity(ID)->setTransparent(enabled);
}

vec3 FabiEngine3D::billboardEntity_getPosition(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getTranslation();
}

vec3 FabiEngine3D::billboardEntity_getRotation(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getRotation();
}

vec2 FabiEngine3D::billboardEntity_getSize(const string& ID)
{
	return vec2(_core->_billboardEntityManager.getEntity(ID)->getScaling().x, _core->_billboardEntityManager.getEntity(ID)->getScaling().y);
}

vec3 FabiEngine3D::billboardEntity_getColor(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getColor();
}

vector<string> FabiEngine3D::billboardEntity_getAllIDs()
{
	vector<string> IDs;

	for (auto entity : _core->_billboardEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

void FabiEngine3D::billboardEntity_setCameraFacingX(const string& ID, bool enabled)
{
	_core->_billboardEntityManager.getEntity(ID)->setCameraFacingX(enabled);
}

void FabiEngine3D::billboardEntity_setCameraFacingY(const string& ID, bool enabled)
{
	_core->_billboardEntityManager.getEntity(ID)->setCameraFacingY(enabled);
}

void FabiEngine3D::billboardEntity_setMaxY(const string& ID, float y)
{
	_core->_billboardEntityManager.getEntity(ID)->setMaxY(y);
}

bool FabiEngine3D::billboardEntity_isFacingCameraX(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isCameraFacingX();
}

bool FabiEngine3D::billboardEntity_isFacingCameraY(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isCameraFacingY();
}

void FabiEngine3D::billBoardEntity_setFont(const string& ID, const string& fontPath)
{
	string text = _core->_billboardEntityManager.getEntity(ID)->getTextContent();
	_core->_billboardEntityManager.getEntity(ID)->setFontPath(fontPath);

	// Only update texture if text content is present
	if (text != "")
	{
		_core->_billboardEntityManager.getEntity(ID)->setDiffuseMap(_core->_texLoader.getText(text, fontPath));
		_core->_billboardEntityManager.getEntity(ID)->setTransparent(true);
	}
}

void FabiEngine3D::billBoardEntity_setTextContent(const string& ID, const string& textContent)
{
	string fontPath = _core->_billboardEntityManager.getEntity(ID)->getFontPath();
	_core->_billboardEntityManager.getEntity(ID)->setTextContent(textContent);

	// Only update texture if font is loaded
	if (fontPath != "")
	{
		_core->_billboardEntityManager.getEntity(ID)->setDiffuseMap(_core->_texLoader.getText(textContent, fontPath));
		_core->_billboardEntityManager.getEntity(ID)->setTransparent(true);
	}
}

const string& FabiEngine3D::billboardEntity_getFontPath(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getFontPath();
}

const string& FabiEngine3D::billboardEntity_getTextContent(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getTextContent();
}

void FabiEngine3D::billBoardEntity_playSpriteAnimation(const string& ID, int maxAnimationRepeats)
{
	_core->_billboardEntityManager.getEntity(ID)->playSpriteAnimation(maxAnimationRepeats);
}

void FabiEngine3D::billboardEntity_stopSpriteAnimation(const string& ID)
{
	_core->_billboardEntityManager.getEntity(ID)->stopSpriteAnimation();
}

void FabiEngine3D::billboardEntity_setAnimationRows(const string& ID, int rows)
{
	_core->_billboardEntityManager.getEntity(ID)->setTotalSpriteRows(rows);
}

void FabiEngine3D::billboardEntity_setAnimationColumns(const string& ID, int columns)
{
	_core->_billboardEntityManager.getEntity(ID)->setTotalSpriteColumns(columns);
}

void FabiEngine3D::billboardEntity_setAnimationFramestep(const string& ID, int framestep)
{
	_core->_billboardEntityManager.getEntity(ID)->setMaxFramestep(framestep);
}

void FabiEngine3D::billboardEntity_setUvRepeat(const string& ID, float repeat)
{
	_core->_billboardEntityManager.getEntity(ID)->setUvRepeat(repeat);
}

const string& FabiEngine3D::billboardEntity_getDiffuseMapPath(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getDiffuseMapPath();
}

bool FabiEngine3D::billboardEntity_isAnimationFinished(const string& ID)
{
	int repeats = _core->_billboardEntityManager.getEntity(ID)->getAnimationRepeats();
	int maxRepeats = _core->_billboardEntityManager.getEntity(ID)->getMaxAnimationRepeats();
	return (repeats == maxRepeats);
}

bool FabiEngine3D::billboardEntity_isAnimationPlaying(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->hasSpriteAnimation();
}

bool FabiEngine3D::billboardEntity_isTransparent(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isTransparent();
}

float FabiEngine3D::billboardEntity_getUvRepeat(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getUvRepeat();
}

int FabiEngine3D::billboardEntity_getAnimationRows(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getTotalSpriteRows();
}

int FabiEngine3D::billboardEntity_getAnimationColumns(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getTotalSpriteColumns();
}

int FabiEngine3D::billboardEntity_getAnimationFramestep(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getMaxFramestep();
}