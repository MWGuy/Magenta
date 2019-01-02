#pragma once

#include "Window.h"
#include "EventHandler.h"
#include "SFML/Graphics.hpp"
#include "Rect.h"
#include "ValueAnimation.h"
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

	enum FocusPolicy {
		NoFocus,
		AutoFocus,
		ManualFocus,
		AlwaysFocus
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

	protected:
		std::vector<void*> dependency;

	public:
		ValueAnimation createValueAnimation(Seconds duration);

		// Visibility

	protected:
		bool visible;

	public:

		void hide();
		void show();
		void toggleVisibility();
		bool isVisible() const;

		// Focus

		FocusPolicy focusPolicy;
		bool isFocused();
		void focus();
		void blur();

		// Attributes

		WidgetId id;
		
		Position position;
		double height$, width$; // %
		double x, y, width, height;

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
		WidgetEventHandler onfocus;
		WidgetEventHandler onblur;
		WidgetEventHandler onshow;
		WidgetEventHandler onhide;
		KeyboardEventHandler onkeydown;
		KeyboardEventHandler onkeyup;
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
