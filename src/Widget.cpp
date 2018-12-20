#include "Widget.h"
#include <iostream>
#include <gdiplus.h>

namespace Magenta
{
	Layout* Widget::layout() {
		return pLayout;
	}

	Widget* Widget::parent() {
		return pParent;
	}

	bool Widget::isRoot() {
		return pParent == 0;
	}

	Rect& Widget::computedRect() {
		return mComputedRect;
	}

#define crect mComputedRect

	void Widget::computeRect()
	{
		if (isRoot()) {
			crect.left = 0;
			crect.top = 0;
			crect.right = layout()->getWindow()->width() - 2;
			crect.bottom = layout()->getWindow()->height() - 2;
			for (size_t i = 0; i < childs.size(); i++)
				childs[i].computeRect();
			return;
		}

		unsigned long w = relativeWidth / 100 * parent()->computedRect().width() - width;
		unsigned long h = relativeHeight / 100 * parent()->computedRect().height() - height;

		switch (position)
		{
		case TopLeft:
			crect.left = 0;
			crect.top = 0;
			break;
		case TopCenter:
			crect.left = parent()->computedRect().width() /2 - w /2;
			crect.top = 0;
			break;
		case TopRight:
			crect.left = parent()->computedRect().width() - w;
			crect.top = 0;
			break;
		case CenterLeft:
			crect.left = 0;
			crect.top = parent()->computedRect().height() / 2 - h / 2;
			break;
		case CenterCenter:
			crect.left = parent()->computedRect().width() / 2 - w / 2;
			crect.top = parent()->computedRect().height() / 2 - h / 2;
			break;
		case CenterRight:
			crect.left = parent()->computedRect().width() - w;
			crect.top = parent()->computedRect().height() / 2 - h / 2;
			break;
		case BottomLeft:
			crect.left = 0;
			crect.top = parent()->computedRect().height() - h;
			break;
		case BottomCenter:
			crect.left = parent()->computedRect().width() / 2 - w / 2;
			crect.top = parent()->computedRect().height() - h;
			break;
		case BottomRight:
			crect.left = parent()->computedRect().width() - w;
			crect.top = parent()->computedRect().height() - h;
			break;
		}
		crect.left += x + parent()->computedRect().left;
		crect.top += y + parent()->computedRect().top;
		crect.setWidth(w);
		crect.setHeight(h);

		for (size_t i = 0; i < childs.size(); i++)
			childs[i].computeRect();
	}

	Widget* Widget::getMouseTargetObject(unsigned int mx, unsigned int my)
	{
		mx -= computedRect().left;
		my -= computedRect().top;

		/* Если что, ``mx`` и ``my`` меньше нуля быть не могут, а
		   если установить -1, то он станет самым большим числом.
		*/

		if(!mx <= computedRect().width() || !mx <= computedRect().height())
			return 0;

		for (size_t i = 0; i < childs.size(); i++) {
			Widget* candidate = childs[i].getMouseTargetObject(mx, my);
			if (candidate != 0)
				return candidate;
		}
		return this;
	}

	void Widget::draw()
	{
#ifdef _WIN32
		HDC          hdc;
		PAINTSTRUCT  ps;

		hdc = BeginPaint(layout()->getWindow()->handler(), &ps);

		Gdiplus::Graphics graphics(hdc);
		Gdiplus::Rect rect;
		rect.X = computedRect().left;
		rect.Y = computedRect().top;
		rect.Width = computedRect().width();
		rect.Height = computedRect().height();
		Gdiplus::Pen pen(Gdiplus::Color(0, 0, 255), 1);
		graphics.DrawRectangle(&pen, rect);

		EndPaint(layout()->getWindow()->handler(), &ps);
#endif
		drawChilds();
	}

	void Widget::drawChilds()
	{
		for (size_t i = 0; i < childs.size(); i++)
			childs[i].draw();
	}

	Widget::Widget(Layout* aLayout, Widget* aParent, unsigned long aId)
		: pLayout(aLayout), pParent(aParent), mComputedRect(), id(aId),
		position(TopLeft), relativeHeight(0), relativeWidth(0), x(0), y(0),
		width(0), height(0),

		onclick(EventUnset),
		onclicknotthis(EventUnset),
		onrightmouseclick(EventUnset),
		onmousedown(EventUnset),
		onmousemove(EventUnset),
		onmouseover(EventUnset),
		onmouseup(EventUnset)
	{
		if (id == AutoId)
			id = rand();
	}

	Frame::Frame(Layout* aLayout, Widget* aParent, unsigned long aId)
		: Widget(aLayout, aParent, aId)
	{
	}

	Frame* createFrame(Widget* owner, unsigned long aId) {
		owner->childs.push_back(Frame(owner->layout(), owner, aId));
		return (Frame*)&owner->childs[owner->childs.size() - 1];
	}
}
