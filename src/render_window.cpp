#include "render_window.hpp"
#include "logger.hpp"
#include "configuration.hpp"

#include <SDL_syswm.h>

RenderWindow::RenderWindow(SDL_Window* windowPointer)
	:
	_windowPointer(windowPointer)
{
	hideBorder();
	setVsyncEnabled(false);
}

RenderWindow::~RenderWindow()
{
	SDL_DestroyWindow(_windowPointer);
}

void RenderWindow::setTitle(const string& title)
{
	SDL_SetWindowTitle(_windowPointer, title.c_str());
}

void RenderWindow::setSize(const ivec2& size)
{
	SDL_SetWindowSize(_windowPointer, size.x, size.y);
	center();
}

void RenderWindow::center()
{
	SDL_SetWindowPosition(_windowPointer, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void RenderWindow::setOpacity(float value)
{
	SDL_SetWindowOpacity(_windowPointer, value);
}

void RenderWindow::enableColorKeying(const fvec3& color)
{
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(_windowPointer, &wmInfo);
	HWND hwnd = wmInfo.info.win.window;

	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd, RGB(static_cast<int>(color.r * 255.0f), static_cast<int>(color.g * 255), static_cast<int>(color.b * 255)), 0, LWA_COLORKEY);
}

void RenderWindow::disableColorKeying(const fvec3& color)
{
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(_windowPointer, &wmInfo);
	HWND hwnd = wmInfo.info.win.window;

	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd, RGB(static_cast<int>(color.r * 255.0f), static_cast<int>(color.g * 255), static_cast<int>(color.b * 255)), 0, LWA_ALPHA);
}

void RenderWindow::showBorder()
{
	SDL_SetWindowBordered(_windowPointer, SDL_TRUE);
}

void RenderWindow::hideBorder()
{
	SDL_SetWindowBordered(_windowPointer, SDL_FALSE);
}

void RenderWindow::enableFullscreen()
{
	SDL_SetWindowFullscreen(_windowPointer, SDL_TRUE);
}

void RenderWindow::disableFullscreen()
{
	SDL_SetWindowFullscreen(_windowPointer, SDL_FALSE);
}

void RenderWindow::setVsyncEnabled(bool value)
{
	SDL_GL_SetSwapInterval(static_cast<int>(value));
}

void RenderWindow::swapBackBuffer()
{
	SDL_GL_SwapWindow(_windowPointer);
}

void RenderWindow::showWindow()
{
	SDL_ShowWindow(_windowPointer);
}

void RenderWindow::hideWindow()
{
	SDL_HideWindow(_windowPointer);
}

void RenderWindow::showCursor()
{
	SDL_ShowCursor(SDL_ENABLE);
}

void RenderWindow::hideCursor()
{
	SDL_ShowCursor(SDL_DISABLE);
}

void RenderWindow::setCursorPosition(const ivec2& pos)
{
	int x = pos.x;
	int y = (Configuration::getInst().getWindowSize().y - pos.y);

	SDL_WarpMouseInWindow(_windowPointer, x, y);
}

const ivec2 RenderWindow::getCursorPosition() const
{
	int x, y;

	SDL_GetMouseState(&x, &y);

	return ivec2(x, (Configuration::getInst().getWindowSize().y - y));
}

const bool RenderWindow::isCursorVisible() const
{
	return static_cast<bool>(SDL_ShowCursor(SDL_QUERY));
}

const bool RenderWindow::isVsyncEnabled() const
{
	return SDL_GL_GetSwapInterval();
}