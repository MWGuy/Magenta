#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif
#include "Layout.h"
#include <string>

#define window_min_width 660
#define window_min_height 420

namespace Magenta
{
	class Window {
#ifdef _WIN32
		HWND hWnd;
#endif
		Layout mLayout;

	public:
		bool isMaximized();
		void toggleMaximize();
		void minimize();

		unsigned int height();
		unsigned int width();

		Layout& layout();

		void alert(std::string message);


#ifdef _WIN32
		HWND handler();

		Window(HWND h, void(*form)(Widget& view));
		Window(HWND h);
#endif
	};
}
