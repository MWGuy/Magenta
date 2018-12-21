#include "Layout.h"
#include "Window.h"
#include "Widget.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

namespace Magenta
{
	Layout::Layout(Window* owner, std::string ymltext) : pWindow(owner), pRoot(new Frame(this, 0))
#ifdef _WIN32
		,view(new Gdiplus::Bitmap(0, 0))
#endif
		, mousemoveWidget(0), mousedownWidget(0)
	{
		update();
	}

	Layout::Layout(Window* owner) : pWindow(owner), pRoot(new Frame(this, 0))
#ifdef _WIN32
		,view(new Gdiplus::Bitmap(0, 0))
#endif
		, mousemoveWidget(0), mousedownWidget(0)
	{
		update();
	}

	Layout::~Layout() {
#ifdef _WIN32
		delete view;
#endif
		delete pRoot;
	}

	Frame* Layout::root() {
		return pRoot;
	}

	Widget* Layout::findWidgetById(unsigned long id) {
		return mIdTable.at(id);
	}

	void Layout::update() {
#ifdef _WIN32
		unsigned long height = getWindow()->height();
		unsigned long width = getWindow()->width();
		delete view;
		view = new Gdiplus::Bitmap(width, height);
#endif
		root()->computeRect();
		root()->draw();
	}

	Window* Layout::getWindow() {
		return pWindow;
	}

	Rect Layout::getClientRect() {
#ifdef _WIN32
		RECT rect;
		GetClientRect(getWindow()->handler(), (LPRECT)&rect);
		return Rect(rect.left, rect.top, rect.right, rect.bottom);
#else
		return Rect();
#endif
	}

	void Layout::unregisterWidget(Widget* self) {
		//mIdTable.erase(self->id);
	}

	void Layout::registerWidget(Widget* self) {
		//std::map<unsigned long, Widget*>::iterator it = mIdTable.begin();
		//mIdTable.insert(it, std::pair<unsigned long, Widget*>(self->id, self));
	}

	Widget* Layout::mouseTargetWidget() {
		unsigned long x, y;
#ifdef _WIN32
		POINT cursor;
		GetCursorPos(&cursor);
		RECT wndRect;
		GetWindowRect(getWindow()->handler(), &wndRect);
		x = cursor.x - wndRect.left;
		y = cursor.y - wndRect.top;
#endif
		return root()->getMouseTargetObject(x, y);
	}

	void Layout::executeOnMouseRightButtonUp() {
		Widget* target = mouseTargetWidget();
		if (mousedownWidget == target)
		{
			if (target->onrightclick != EventUnset)
				target->onrightclick(target);
		}
		mousedownWidget = 0;
	}

	void Layout::executeOnMouseDown() {
		Widget* target = mouseTargetWidget();
		mousedownWidget = target;
		if (target->onmousedown != EventUnset)
			target->onmousedown(target);
	}

	void Layout::executeOnMouseMove() {
		Widget* target = mouseTargetWidget();
		if (target == 0)
			return;

		if (mousemoveWidget != 0) {
			if (mousemoveWidget != target)
			{
				if (mousemoveWidget->onmouseleave != 0)
					mousemoveWidget->onmouseleave(mousemoveWidget);

				mousemoveWidget = target;

				if (mousemoveWidget->onmouseenter != 0)
					mousemoveWidget->onmouseenter(mousemoveWidget);
			}
		} else {
			mousemoveWidget = target;

			if (mousemoveWidget->onmouseenter != 0)
				mousemoveWidget->onmouseenter(mousemoveWidget);
		}

		if (target->onmousemove != EventUnset)
			target->onmousemove(target);
	}

	void Layout::executeOnMouseUp() {
		Widget* target = mouseTargetWidget();
		if (target->onmouseup != EventUnset)
			target->onmouseup(target);
		
		if (mousedownWidget == target)
		{
			if (target->onclick != EventUnset)
				target->onclick(target);
		}
		mousedownWidget = 0;
	}
}
