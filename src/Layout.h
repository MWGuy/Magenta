#pragma once

#ifdef _WIN32
#include <windows.h>
#include "SFML/Graphics.hpp"
#endif
#include "Rect.h"
#include "EventHandler.h"
#include <string>

#define ma_form (Magenta::Widget& view)

namespace Magenta
{
	class Frame_;
	class Window;
	class Widget;
	class Layout {
		Window* pWindow;
		Frame_* pRoot;
	public:
		Layout(Window* owner, void(*form)(Widget& view));
		Layout(Window* owner);
		~Layout();

		Frame_* root();

		Widget* findWidgetById(unsigned long id);

		void update();
		void forceUpdate();

		Window* getWindow();
		Rect getClientRect();

		void unregisterWidget(Widget* self);
		void registerWidget(Widget* self);

		void executeOnMouseRightButtonUp();
		void executeOnMouseDown();
		void executeOnMouseMove();
		void executeOnMouseUp();

		float scale;

		sf::Font font;
		sf::RenderWindow view;

		Widget* mousemoveWidget;
		Widget* mousedownWidget;
		Widget* focusedWidget;

		SharedEventHandler onwindowmaximize;
		SharedEventHandler onwindowrestore;
		SharedEventHandler onmousedown;
		SharedEventHandler onmouserightbuttonup;
		SharedEventHandler onmouseup;
	protected:
		Widget* mouseTargetWidget();
	};
}
