#include "Widget.h"
#include <iostream>
#include <gdiplus.h>

namespace Magenta
{
	void MouseEventHandler::operator+=(MouseEventCallback callback) {
		sequence.push_back(callback);
	}

	void MouseEventHandler::operator=(MouseEventCallback callback)
	{
		sequence.clear();
		sequence.push_back(callback);
	}

	void MouseEventHandler::setWidgetSpecific(MouseEventCallback callback) {
		widgetSpecificCallbacks.push_back(callback);
	}

	Widget& MouseEventHandler::assignedWidget() {
		return *mAssignedWidget;
	}

	void MouseEventHandler::dispatch() {
		for (size_t i = 0; i < widgetSpecificCallbacks.size(); i++)
			widgetSpecificCallbacks[i](*mAssignedWidget);

		for (size_t i = 0; i < sequence.size(); i++)
			sequence[i](*mAssignedWidget);
	}

	MouseEventHandler::MouseEventHandler(Widget* assignedTo) : mAssignedWidget(assignedTo)
	{
	}

	sf::RenderWindow& Widget::canvas() {
		return layout()->view;
	}

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
				childs[i]->computeRect();
			return;
		}

		unsigned long w = width$ / 100 * parent()->computedRect().width() + width;
		unsigned long h = height$ / 100 * parent()->computedRect().height() + height;

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

		// Fix black lines
		if (width$ == 100 && width == 0 && x == 0)
			crect.right++;

		if (crect.bottom > layout()->root()->computedRect().bottom - 1)
			crect.bottom++;

#ifdef DEBUG
		std::string str = std::to_string(crect.left);
		str += ", ";
		str += std::to_string(crect.top);
		str += ", ";
		str += std::to_string(crect.width());
		str += ", ";
		str += std::to_string(h);

		layout()->getWindow()->alert(str);
#endif

		for (size_t i = 0; i < childs.size(); i++)
			childs[i]->computeRect();
	}

	bool compareZIndex(Widget* i1, Widget* i2)
	{
		return (i1->zIndex > i2->zIndex);
	}

	Widget* Widget::getMouseTargetObject(unsigned int mx, unsigned int my)
	{
		if (!isRoot()) {
			mx -= computedRect().left - parent()->computedRect().left;
			my -= computedRect().top - parent()->computedRect().top;
		}

		/* ���� ���, ``mx`` � ``my`` ������ ���� ���� �� �����, �
		   ���� ���������� -1, �� �� ������ ����� ������� ������.
		*/

		if (mx > computedRect().width() || my > computedRect().height())
			return 0;

		std::vector<Widget*> sequence = childs;
		std::sort(sequence.begin(), sequence.end(), compareZIndex);

		for (size_t i = 0; i < sequence.size(); i++) {
			Widget* candidate = sequence[i]->getMouseTargetObject(mx, my);
			if (candidate != 0)
				return candidate;
		}
		return this;
	}

	void Widget::draw()
	{
		sf::RectangleShape wrect(sf::Vector2f(computedRect().width(), computedRect().height()));
		wrect.setPosition(computedRect().left, computedRect().top);
		wrect.setFillColor(sf::Color(0, 0, 255, 40));
		canvas().draw(wrect);

		drawChilds();
	}

	void Widget::drawChilds()
	{
		std::vector<Widget*> sequence = childs;
		std::sort(sequence.begin(), sequence.end(), compareZIndex);

		for (size_t i = 0; i < sequence.size(); i++)
			sequence[i]->draw();
	}

	Widget::Widget(Layout* aLayout, Widget* aParent, unsigned long aId)
		: pLayout(aLayout), pParent(aParent), mComputedRect(), id(aId),
		position(TopLeft), height$(0), width$(0), x(0), y(0), zIndex(0),
		width(0), height(0),

		onclick(this),
		onrightclick(this),
		onmousedown(this),
		onmousemove(this),
		onmouseenter(this),
		onmouseleave(this),
		onmouseup(this)
	{
		if (id == AutoId)
			id = rand();

		layout()->registerWidget(this);
	}

	Widget::~Widget() {
		layout()->unregisterWidget(this);
		for (size_t i = 0; i < childs.size(); i++) {
			if (layout()->mousedownWidget == childs[i])
				layout()->mousedownWidget = 0;
			if (layout()->mousemoveWidget == childs[i])
				layout()->mousemoveWidget = 0;
			delete childs[i];
		}
	}

	Widget& Widget::operator[](size_t index) {
		return *childs[index];
	}

	void Widget::remove() {
		if (isRoot())
			return;

		if (layout()->mousedownWidget == this)
			layout()->mousedownWidget = 0;

		if (layout()->mousemoveWidget == this)
			layout()->mousemoveWidget = 0;

		for (size_t i = 0; i < parent()->childs.size(); i++)
		{
			if (parent()->childs[i] == this) {
				parent()->childs.erase(parent()->childs.begin() + i);
				break;
			}
		}

		delete this;
	}

	Frame_::Frame_(Layout* aLayout, Widget* aParent, unsigned long aId)
		: Widget(aLayout, aParent, aId)
	{
	}

	Frame createFrame(Widget& owner, unsigned long aId) {
		owner.childs.push_back(new Frame_(owner.layout(), &owner, aId));
		return (Frame)*owner.childs[owner.childs.size() - 1];
	}

	void removeWidget(Widget& self) {
		Layout* l = self.layout();
		self.remove();
		l->update();
	}
}
