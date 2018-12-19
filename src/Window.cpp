#include "Window.h"
#include "stdafx.h"

namespace Magenta
{
	bool Window::isMaximized() {
#ifdef _WIN32
		return GetClassLong(hWnd, -26) == 3;
#endif
	}

	void Window::toggleMaximize() {
#ifdef _WIN32
		isMaximized() ? SetClassLong(hWnd, -26, 1) : SetClassLong(hWnd, -26, 3);
#endif
	}

	void Window::minimize() {
#ifdef _WIN32
		CloseWindow(hWnd);
#endif
	}

	Layout& Window::layout() {
#ifdef _WIN32
		return mLayout;
#endif
	}

#ifdef _WIN32
	HWND Window::handler() {
		return hWnd;
	}

	Window::Window(HWND h, std::string layoutjson) : hWnd(h), mLayout(this, layoutjson)
	{
	}

	Window::Window(HWND h) : hWnd(h), mLayout(this)
	{
	}
#endif
}
