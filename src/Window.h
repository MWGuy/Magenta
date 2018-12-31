#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif
#include "Layout.h"
#include <string>

#define window_min_width 660
#define window_min_height 420

// shared
enum WindowTransform {
	Idle,
	SizingLeft,
	SizingLeftTop,
	SizingLeftBottom,
	SizingRight,
	SizingRightTop,
	SizingRightBottom,
	SizingTop,
	SizingBottom,
	Moving
};

namespace Magenta
{
	class Window {
#ifdef _WIN32
		HWND hInner;
		HWND hWnd;
		bool mMaximized;

		unsigned int savedX;
		unsigned int savedY;
		unsigned int savedHeight;
		unsigned int savedWidth;
#endif
		Layout mLayout;
		WindowTransform* mWinTransform;
		bool mIsLoaded;

	public:
		bool isLoaded() const;
		bool isMaximized() const;
		void toggleMaximize();
		void minimize();

		void close();

		unsigned int height();
		unsigned int width();

		Layout& layout();

		void alert(std::string message);

		void setTransformable(WindowTransform* wtransform);
		void setTransform(WindowTransform state);

#ifdef _WIN32
		HWND handler();

		Window(HWND i, HWND h, void(*form)(Widget& view), WindowTransform* wtransform = 0);
		Window(HWND i, HWND h, WindowTransform* wtransform = 0);
#endif

		void setLoaded();
	};
}
