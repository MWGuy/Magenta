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
	{
		update();
	}

	Layout::Layout(Window* owner) : pWindow(owner), pRoot(new Frame(this, 0))
	{
		update();
	}

	Layout::~Layout() {
		delete pRoot;
	}

	Frame* Layout::root() {
		return pRoot;
	}

	Widget* Layout::findWidgetById(unsigned long id) {
		return mIdTable.at(id);
	}

	void Layout::update() {
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
}
