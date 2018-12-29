#include "Layout.h"
#include "Window.h"
#include "Widget.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

namespace Magenta
{
	Layout::Layout(Window* owner, void(*form)(Widget& view)) : pWindow(owner), pRoot(new Frame_(this, 0)),
		scale(1.0), view(owner->handler(), sf::ContextSettings(24, 8, 8)),
		mousemoveWidget(0), mousedownWidget(0)
	{
		if (!font.loadFromFile("resources/fonts/third-party/Arimo-Regular.ttf")) {
			MessageBox(0, "Missing font resources", "Magenta", MB_OK);
		}

		form(*root());
		update();
	}

	Layout::Layout(Window* owner) : pWindow(owner), pRoot(new Frame_(this, 0)),
		scale(1.0), view(owner->handler(), sf::ContextSettings(24, 8, 8)),
		mousemoveWidget(0), mousedownWidget(0)
	{
		if (!font.loadFromFile("resources/fonts/third-party/Arimo-Regular.ttf")) {
			MessageBox(0, "Missing font resources", "Magenta", MB_OK);
		}

		update();
	}

	Layout::~Layout() {
		view.close();
		delete pRoot;
	}

	Frame_* Layout::root() {
		return pRoot;
	}

	Widget* findWidgetByIdRecursive(Widget* current, unsigned long id) {
		if (current->id == id)
			return current;

		for (unsigned i = 0; i < current->childs.size(); i++)
		{
			Widget* candidate = findWidgetByIdRecursive(current->childs[i], id);
			if (candidate != 0)
				return candidate;
		}
		return 0;
	}

	Widget* Layout::findWidgetById(unsigned long id) {
		return findWidgetByIdRecursive(root(), id);
	}

	void Layout::update() {
		unsigned long height = getWindow()->height();
		unsigned long width = getWindow()->width();

		view.setSize(sf::Vector2u(width, height));
		view.setView(sf::View(sf::FloatRect(0, 0, width, height)));
		view.clear(sf::Color(255, 255, 255));

		root()->computeRect();
		root()->draw();

		view.display();
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
		
	}

	void Layout::registerWidget(Widget* self) {
		
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
		onmouserightbuttonup.dispatchAll();
		Widget* target = mouseTargetWidget();
		if (target == 0)
			return;

		if (mousedownWidget == target)
		{
			target->onrightclick.dispatch();
		}
		mousedownWidget = 0;
	}

	void Layout::executeOnMouseDown() {
		onmousedown.dispatchAll();
		Widget* target = mouseTargetWidget();
		if (target == 0)
			return;

		mousedownWidget = target;
		target->onmousedown.dispatch();
	}

	void Layout::executeOnMouseMove() {
		Widget* target = mouseTargetWidget();
		if (target == 0)
		{
			if (mousemoveWidget != 0) {
				if (mousemoveWidget != target)
				{
					mousemoveWidget->onmouseleave.dispatch();
					mousemoveWidget = 0;
				}
			}
			return;
		}

		if (mousemoveWidget != 0) {
			if (mousemoveWidget != target)
			{
				mousemoveWidget->onmouseleave.dispatch();

				mousemoveWidget = target;

				mousemoveWidget->onmouseenter.dispatch();
			}
		} else {
			mousemoveWidget = target;

			mousemoveWidget->onmouseenter.dispatch();
		}

		target->onmousemove.dispatch();
	}

	void Layout::executeOnMouseUp() {
		onmouseup.dispatchAll();
		Widget* target = mouseTargetWidget();
		if (target == 0)
			return;
		
		target->onmouseup.dispatch();
		
		if (mousedownWidget == target)
		{
			target->onclick.dispatch();
		}
		mousedownWidget = 0;
	}
}
