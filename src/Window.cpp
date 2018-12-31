#include "Window.h"

namespace Magenta
{
	bool Window::isLoaded() const {
		return mIsLoaded;
	}

	bool Window::isMaximized() const {
		return mMaximized;
	}

	void Window::toggleMaximize() {
#ifdef _WIN32
		if(isMaximized())
		{
			mMaximized = false;
			CloseWindow(hWnd);
			MoveWindow(hInner, savedX, savedY, savedWidth, savedHeight, false);
			ShowWindow(hWnd, SW_SHOWNORMAL);
			layout().onwindowrestore.dispatchAll();
		}
		else
		{
			mMaximized = true;
			RECT rect;
			GetWindowRect(hInner, (LPRECT)&rect);
			savedX = rect.left;
			savedY = rect.top;
			savedWidth = rect.right - rect.left;
			savedHeight = rect.bottom - rect.top;
			RECT workArea;
			SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0); // deprecated
			MoveWindow(hInner, 0, 0, workArea.right, workArea.bottom, true);
			SetWindowRgn(hInner, NULL, true);
			layout().onwindowmaximize.dispatchAll();
		}
#endif
	}

	void Window::minimize() {
#ifdef _WIN32
		CloseWindow(hWnd);
#endif
	}

	void Window::close() {
#ifdef _WIN32
		PostMessage(hWnd, WM_CLOSE, NULL, NULL);
#endif
	}

	unsigned int Window::height() {
#ifdef _WIN32
		RECT rect;
		GetClientRect(hInner, (LPRECT)&rect);
		return rect.bottom - rect.top;
#endif
	}
	unsigned int Window::width() {
#ifdef _WIN32
		RECT rect;
		GetClientRect(hInner, (LPRECT)&rect);
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
		return hInner;
	}

	Window::Window(HWND i, HWND h, void(*form)(Widget& view), WindowTransform* wtransform)
		: hInner(i), hWnd(h), mMaximized(false), savedX(0), savedY(0), savedHeight(0), savedWidth(0),
		mLayout(this, form), mWinTransform(wtransform), mIsLoaded(false)
	{
	}

	Window::Window(HWND i, HWND h, WindowTransform* wtransform) : hInner(i), hWnd(h), mMaximized(false), savedX(0), savedY(0),
		savedHeight(0), savedWidth(0), mLayout(this), mWinTransform(wtransform), mIsLoaded(false)
	{
	}
#endif

	void Window::setLoaded() {
		mIsLoaded = true;
	}
}
