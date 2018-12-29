#pragma once

#include "Window.h"
#include "EventHandler.h"
#include "SFML/Graphics.hpp"
#include "Rect.h"
#include <vector>

namespace Magenta
{
	typedef unsigned long WidgetId;
	const unsigned long AutoId = -1;

	enum Position {
		TopLeft,
		TopCenter,
		TopRight,
		CenterLeft,
		CenterCenter,
		CenterRight,
		BottomLeft,
		BottomCenter,
		BottomRight
	};

	class Widget {
		Layout* pLayout;
		Widget* pParent;
		Rect mComputedRect;
	public:

		sf::RenderWindow& canvas();
		void update();

		Layout* layout();

		Widget* parent();
		bool isRoot();

		Rect& computedRect();
		void computeRect();

		Widget* getMouseTargetObject(unsigned int mx, unsigned int my);

		virtual void draw();
		void drawChilds();

		Widget(Layout* aLayout, Widget* aParent, unsigned long aId = AutoId);
		virtual ~Widget();

		Widget& operator[](size_t index);

		void remove();

		// Visibility

	protected:
		bool visible;

	public:

		void hide();
		void show();
		void toggleVisibility();
		bool isVisible() const;

		// Attributes

		WidgetId id;
		
		Position position;
		double height$, width$; // %
		int x, y, width, height;

		long zIndex;

		std::vector<Widget*> childs;

		// Events

		MouseEventHandler onclick;
		MouseEventHandler onrightclick;
		MouseEventHandler onmousedown;
		MouseEventHandler onmousemove;
		MouseEventHandler onmouseenter;
		MouseEventHandler onmouseleave;
		MouseEventHandler onmouseup;
		WidgetEventHandler onshow;
		WidgetEventHandler onhide;
	};

	// Common widgets

	class Frame_ : public Widget {
	public:
		Frame_(Layout* aLayout, Widget* aParent, unsigned long aId = AutoId);
	};
	typedef Frame_& Frame;

	Frame createFrame(Widget& owner, unsigned long aId = AutoId);

	// Common callbacks

	void removeWidget(Widget& self);
}
