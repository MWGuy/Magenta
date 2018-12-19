#pragma once

#include "stdafx.h"

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

		Layout& layout();

#ifdef _WIN32
		HWND handler();

		Window(HWND h, std::string layoutjson);
		Window(HWND h);
#endif
	};
}
