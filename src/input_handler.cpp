#include "input_handler.hpp"

#include <SDL\\SDL.h>

void InputHandler::update()
{
	_keysPressed.clear();
	_mousePressed.clear();
	_mouseWheelX = 0;
	_mouseWheelY = 0;

	SDL_Event event;

	if(!_isLocked)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
				{
					_keysDown.push_back(static_cast<InputType>(SDL_QUIT));
					break;
				}

				case SDL_MOUSEWHEEL:
				{
					_mouseWheelX = event.wheel.x;
					_mouseWheelY = event.wheel.y;
					break;
				}

				case SDL_MOUSEBUTTONDOWN:
				{
					auto button = static_cast<InputType>(event.button.button);

					if(!_isInVector(_mouseDown, button))
					{
						_mouseDown.push_back(button);
					}

					if(!_isInVector(_mousePressed_mayNotPress, button))
					{
						_mousePressed.push_back(button);
						_mousePressed_mayNotPress.push_back(button);
					}

					break;
				}

				case SDL_MOUSEBUTTONUP:
				{
					auto button = static_cast<InputType>(event.button.button);

					if(!_mouseDown.empty())
					{
						_mouseDown.erase(_mouseDown.begin() + _getVectorIndex(_mouseDown, button));
					}

					_mousePressed_mayNotPress.clear();

					break;
				}

				case SDL_KEYDOWN:
				{
					auto key = static_cast<InputType>(event.key.keysym.sym);

					if(!_isInVector(_keysDown, key))
					{
						_keysDown.push_back(key);
					}

					if(!_isInVector(_keysPressed_mayNotPress, key))
					{
						_keysPressed.push_back(key);
						_keysPressed_mayNotPress.push_back(key);
					}

					break;
				}

				case SDL_KEYUP:
				{
					auto key = static_cast<InputType>(event.key.keysym.sym);

					if(!_keysDown.empty())
					{
						_keysDown.erase(_keysDown.begin() + _getVectorIndex(_keysDown, key));
					}

					_keysPressed_mayNotPress.clear();

					break;
				}
			}
		}
	}
}

void InputHandler::setLocked(bool locked)
{
	_isLocked = locked;
}

const bool InputHandler::isLocked() const
{
	return _isLocked;
}

const bool InputHandler::isKeyDown(InputType key) const
{
	return _isInVector(_keysDown, key);
}

const bool InputHandler::isKeyPressed(InputType key) const
{
	return _isInVector(_keysPressed, key);
}

const bool InputHandler::isMouseDown(InputType button) const
{
	return _isInVector(_mouseDown, button);
}

const bool InputHandler::isMousePressed(InputType button) const
{
	return _isInVector(_mousePressed, button);
}

const int InputHandler::getMouseWheelX() const
{
	return _mouseWheelX;
}

const int InputHandler::getMouseWheelY() const
{
	return _mouseWheelY;
}