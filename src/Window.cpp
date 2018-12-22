#include "Window.h"

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

	unsigned int Window::height() {
#ifdef _WIN32
		RECT rect;
		GetClientRect(hWnd, (LPRECT)&rect);
		return rect.bottom - rect.top;
#endif
	}
	unsigned int Window::width() {
#ifdef _WIN32
		RECT rect;
		GetClientRect(hWnd, (LPRECT)&rect);
		return rect.right - rect.left;
#endif
	}

	Layout& Window::layout() {
#ifdef _WIN32
		return mLayout;
#endif
	}
	void Window::alert(std::string message) {
#ifdef _WIN32
		HDC hdc = GetDC(hWnd);

		TextOut(hdc, 0, 0, (LPTSTR)message.c_str(), message.size());

		ReleaseDC(hWnd, hdc);
#endif
	}

	void Window::setTransformable(WindowTransform* wtransform) {
		mWinTransform = wtransform;
	}

	void Window::setTransform(WindowTransform state) {
		if(mWinTransform != 0)
			*mWinTransform = state;
	}

#ifdef _WIN32
	HWND Window::handler() {
		return hWnd;
	}

	Window::Window(HWND h, void(*form)(Widget& view), WindowTransform* wtransform)
		: hWnd(h), mLayout(this, form), mWinTransform(wtransform)
	{
	}

	Window::Window(HWND h, WindowTransform* wtransform) : hWnd(h), mLayout(this), mWinTransform(wtransform)
	{
	}
#endif
}
