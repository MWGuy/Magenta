#pragma once

#include "Window.h"
#include "Rect.h"
#include <vector>

#define EventUnset 0

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

		Layout* layout();

		Widget* parent();
		bool isRoot();

		Rect& computedRect();
		void computeRect();

		Widget* getMouseTargetObject(unsigned int mx, unsigned int my);

		virtual void draw();
		void drawChilds();

		Widget(Layout* aLayout, Widget* aParent, unsigned long aId = AutoId);
		~Widget();

		void remove();

		// Attributes

		WidgetId id;
		
		Position position;
		double relativeHeight, relativeWidth; // %
		int x, y, width, height;

		std::vector<Widget> childs;

		// Events

		void (*onclick)(Widget* self);
		void(*onrightclick)(Widget* self);
		void(*onmousedown)(Widget* self);
		void(*onmousemove)(Widget* self);
		void(*onmouseenter)(Widget* self);
		void(*onmouseleave)(Widget* self);
		void(*onmouseup)(Widget* self);
	};

	class Frame : public Widget {
	public:
		Frame(Layout* aLayout, Widget* aParent, unsigned long aId = AutoId);
	};

	Frame* createFrame(Widget* owner, unsigned long aId = AutoId);

	void removeWidget(Widget* self);
}
