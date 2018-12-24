#pragma once

#ifdef _WIN32
#include <windows.h>
#include "SFML/Graphics.hpp"
#endif
#include "Rect.h"
#include <string>
#include <map>

#define ma_form (Magenta::Widget& view)

namespace Magenta
{
	class Frame_;
	class Window;
	class Widget;
	class Layout {
		Window* pWindow;
		Frame_* pRoot;
		std::map<unsigned long, Widget*> mIdTable;
	public:
		Layout(Window* owner, void(*form)(Widget& view));
		Layout(Window* owner);
		~Layout();

		Frame_* root();

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

		float scale;

		sf::Font font;
		sf::RenderWindow view;

		Widget* mousemoveWidget;
		Widget* mousedownWidget;
	protected:
		Widget* mouseTargetWidget();
	};
}
