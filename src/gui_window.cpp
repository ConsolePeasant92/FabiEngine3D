#include "gui_window.hpp"
#include "tools.hpp"

GuiWindow::GuiWindow(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const fvec3 & color)
	:
	_id(id),
	_parentId(parentId),
	_quad2dId("@@" + parentId + "_" + id)
{
	if(_id.empty())
	{
		abort();
	}

	_fe3d = fe3d;

	_fe3d->quad2d_create(_quad2dId, true);
	_fe3d->quad2d_setPosition(_quad2dId, position);
	_fe3d->quad2d_setSize(_quad2dId, size);
	_fe3d->quad2d_setColor(_quad2dId, color);
}

GuiWindow::~GuiWindow()
{
	_fe3d->quad2d_delete(_quad2dId);
}

void GuiWindow::update(bool isInteractable)
{
	_updateHovering(isInteractable);

	for(const auto & [screenId, screen] : _screens)
	{
		screen->update(isInteractable);

		screen->setVisible(screenId == _activeScreenId);
	}
}

const bool GuiWindow::hasScreen(const string & screenId) const
{
	return (_screens.find(screenId) != _screens.end());
}

const bool GuiWindow::isHovered() const
{
	return _isHovered;
}

void GuiWindow::_updateHovering(bool isInteractable)
{
	_isHovered = false;

	const auto cursorPosition = Tools::convertToNdc(Tools::getCursorPosition());
	const auto windowPosition = getPosition();
	const auto windowSize = getSize();

	if(cursorPosition.x > (windowPosition.x - (windowSize.x * 0.5f)))
	{
		if(cursorPosition.x < (windowPosition.x + (windowSize.x * 0.5f)))
		{
			if(cursorPosition.y > (windowPosition.y - (windowSize.y * 0.5f)))
			{
				if(cursorPosition.y < (windowPosition.y + (windowSize.y * 0.5f)))
				{
					if(isInteractable)
					{
						_isHovered = true;
					}
				}
			}
		}
	}
}

const string & GuiWindow::getId() const
{
	return _id;
}

const string & GuiWindow::getParentId() const
{
	return _parentId;
}

const fvec3 & GuiWindow::getColor() const
{
	return _fe3d->quad2d_getColor(_quad2dId);
}

const fvec2 & GuiWindow::getPosition() const
{
	return _fe3d->quad2d_getPosition(_quad2dId);
}

const fvec2 & GuiWindow::getSize() const
{
	return _fe3d->quad2d_getSize(_quad2dId);
}

void GuiWindow::createScreen(const string & screenId)
{
	if(hasScreen(screenId))
	{
		abort();
	}

	_screens.insert({screenId, make_shared<GuiScreen>(_fe3d, screenId, (_parentId + "_" + _id), getPosition(), getSize())});
}

void GuiWindow::deleteScreen(const string & screenId)
{
	if(!hasScreen(screenId))
	{
		abort();
	}

	_screens.erase(screenId);

	if(screenId == _activeScreenId)
	{
		_activeScreenId = "";
	}
}

void GuiWindow::deleteScreens()
{
	_screens.clear();
}

void GuiWindow::setActiveScreen(const string & screenId)
{
	if(!hasScreen(screenId))
	{
		abort();
	}

	_activeScreenId = screenId;
}

const unordered_map<string, shared_ptr<GuiScreen>> & GuiWindow::getScreens() const
{
	return _screens;
}

const shared_ptr<GuiScreen> GuiWindow::getActiveScreen() const
{
	return getScreen(_activeScreenId);
}

const shared_ptr<GuiScreen> GuiWindow::getScreen(const string & screenId) const
{
	const auto iterator = _screens.find(screenId);

	if(iterator == _screens.end())
	{
		abort();
	}

	return iterator->second;
}