#pragma once

#include "stdafx.h"
#include "Window.h"
#include "Rect.h"
#include <vector>

namespace Magenta
{
	typedef unsigned long WidgetId;

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

	typedef enum
	{
		Normal,
		WindowCaption
	}
	WidgetBehavior;

	class Widget {
		Layout* pLayout;
		Widget* pParent;
		Rect mComputedRect;
	public:

		Layout* layout();

		Widget* parent();
		bool isRoot();

		Rect& computedRect();
		void computeRect();

		Widget* getMouseTargetObject(unsigned int mx, unsigned int my);

		virtual void draw() {}

		Widget(Layout* aLayout, Widget* aParent);

		// Attributes

		WidgetId id;

		Position position;
		double relativeHeight, relativeWidth; // %
		int x, y, width, height;

		WidgetBehavior behavior;

		std::vector<Widget> childs;

		// Events

		void (*onclick)(Widget* self);
	protected:
		void(*onrightmouseclick)(Widget* self);
		void(*onmousedown)(Widget* self);
		void(*onmousemove)(Widget* self);
		void(*onmouseover)(Widget* self);
		void(*onmouseup)(Widget* self);

		bool mousedown;
	};

	class Frame : public Widget {
	public:
		Frame(Layout* aLayout, Widget* aParent);
	};

	Frame* createFrame(Widget* owner);
}
