#pragma once

#ifdef _WIN32
#include <windows.h>
#include <gdiplus.h>
#endif
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

		void executeOnMouseRightButtonUp();
		void executeOnMouseDown();
		void executeOnMouseMove();
		void executeOnMouseUp();

#ifdef _WIN32
		Gdiplus::Bitmap* view;
#endif
		Widget* mousemoveWidget;
		Widget* mousedownWidget;
	protected:
		Widget* mouseTargetWidget();
	};
}
