#pragma once

#include "Rect.h"
#include <string>
#include <map>

namespace Magenta
{
	class Frame;
	class Window;
	class Widget;
	class Layout {
		Window* pWindow;
		Frame* pRoot;
		std::map<unsigned long, Widget*> mIdTable;
	public:
		Layout(Window* owner, std::string jsontext);
		Layout(Window* owner);
		~Layout();

		Frame* root();

		Widget* findWidgetById(unsigned long id);

		void update();

		Window* getWindow();
		Rect getClientRect();

		void unregisterWidget(Widget* self);
		void registerWidget(Widget* self);
	};
}
