#pragma once

#include "mathematics.hpp"
#include "input_handler.hpp"

#include <string>
#include <windows.h>

using std::shared_ptr;
using std::string;

class RenderWindow final
{
public:
	RenderWindow();

	void inject(shared_ptr<InputHandler> inputHandler);
	void update();
	void setPosition(const ivec2 & value);
	void setSize(const ivec2 & value);
	void setVisible(bool value);
	void setColorKeyingEnabled(bool value);
	void setKeyingColor(const fvec3 & value);
	void setTitle(const string & value);
	void setVsyncEnabled(bool value);
	void swapBuffer();

	const string getTitle() const;

	const fvec3 getKeyingColor() const;

	const ivec2 getPosition() const;
	const ivec2 getSize() const;

	const bool isClosed() const;
	const bool isVisible() const;
	const bool isVsyncEnabled() const;

private:
	static inline constexpr unsigned int MAX_TITLE_LENGTH = 100;

	shared_ptr<InputHandler> _inputHandler = nullptr;

	HWND _windowHandle = nullptr;
};