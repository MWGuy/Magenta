#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif
#include "Layout.h"
#include <string>

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

#ifdef _WIN32
		HWND handler();

		Window(HWND h, std::string layoutyml);
		Window(HWND h);
#endif
	};
}
