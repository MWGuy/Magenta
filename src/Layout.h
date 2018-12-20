#pragma once

#include "Rect.h"
#include <string>

namespace Magenta
{
	class Frame;
	class Window;
	class Layout {
		Window* pWindow;
		Frame* pRoot;
	public:
		Layout(Window* owner, std::string jsontext);
		Layout(Window* owner);
		~Layout();

		Frame* root();

		void update();

		Window* getWindow();
		Rect getClientRect();
	};
}
