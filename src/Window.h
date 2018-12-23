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
		HWND hWnd;
#endif
		Layout mLayout;

		WindowTransform* mWinTransform;

	public:
		bool isMaximized();
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

		Window(HWND h, void(*form)(Widget& view), WindowTransform* wtransform = 0);
		Window(HWND h, WindowTransform* wtransform = 0);
#endif
	};
}
