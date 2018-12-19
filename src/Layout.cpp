#include "Layout.h"
#include "stdafx.h"

namespace Magenta
{
	Layout::Layout(Window* owner, std::string jsontext) : pWindow(owner)
	{

	}

	Layout::Layout(Window* owner) : pWindow(owner)
	{

	}

	Window* Layout::getWindow() {
		return pWindow;
	}
}
