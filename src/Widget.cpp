#include "Widget.h"
#include <iostream>
#include <gdiplus.h>

namespace Magenta
{
	Cursor::Cursor(Variant aVariant, bool aVisible, std::string aSpecified)
		:variant(aVariant), visible(aVisible), specified(aSpecified),
		offsetX(0), offsetY(0)
	{
	}

	void Widget::useCursor()
	{
		sf::Cursor cursor;
		sf::Image img;
		switch (mCursor.variant)
		{
		case Cursor::Default:
			cursor.loadFromSystem(sf::Cursor::Arrow);
			layout()->view.setMouseCursor(cursor);
			break;
		case Cursor::Cross:
			cursor.loadFromSystem(sf::Cursor::Cross);
			layout()->view.setMouseCursor(cursor);
			break;
		case Cursor::Hand:
			cursor.loadFromSystem(sf::Cursor::Hand);
			layout()->view.setMouseCursor(cursor);
			break;
		case Cursor::IBeam:
			cursor.loadFromSystem(sf::Cursor::Text);
			layout()->view.setMouseCursor(cursor);
			break;
		case Cursor::Busy:
			cursor.loadFromSystem(sf::Cursor::Wait);
			layout()->view.setMouseCursor(cursor);
			break;
		case Cursor::Wait:
			cursor.loadFromSystem(sf::Cursor::ArrowWait);
			layout()->view.setMouseCursor(cursor);
			break;
		case Cursor::NotAllowed:
			cursor.loadFromSystem(sf::Cursor::NotAllowed);
			layout()->view.setMouseCursor(cursor);
			break;
		case Cursor::Help:
			cursor.loadFromSystem(sf::Cursor::Help);
			layout()->view.setMouseCursor(cursor);
			break;
		case Cursor::Size:
			cursor.loadFromSystem(sf::Cursor::SizeAll);
			layout()->view.setMouseCursor(cursor);
			break;
		case Cursor::SizeAll:
			cursor.loadFromSystem(sf::Cursor::SizeAll);
			layout()->view.setMouseCursor(cursor);
			break;
		case Cursor::SizeNeSw:
			cursor.loadFromSystem(sf::Cursor::SizeBottomLeftTopRight);
			layout()->view.setMouseCursor(cursor);
			break;
			break;
		case Cursor::SizeNs:
			cursor.loadFromSystem(sf::Cursor::SizeVertical);
			layout()->view.setMouseCursor(cursor);
			break;
		case Cursor::SizeNwSe:
			cursor.loadFromSystem(sf::Cursor::SizeTopLeftBottomRight);
			layout()->view.setMouseCursor(cursor);
			break;
		case Cursor::SizeWe:
			cursor.loadFromSystem(sf::Cursor::SizeHorizontal);
			layout()->view.setMouseCursor(cursor);
			break;
		case Cursor::UpArrow:
			cursor.loadFromSystem(sf::Cursor::Arrow);
			layout()->view.setMouseCursor(cursor);
			break;
		case Cursor::Specified:
			img.loadFromFile(mCursor.specified);
			if (cursor.loadFromPixels(img.getPixelsPtr(), img.getSize(), sf::Vector2u(mCursor.offsetX, mCursor.offsetY)))
				layout()->view.setMouseCursor(cursor);
			break;
		}
		layout()->view.setMouseCursorVisible(mCursor.visible);
	}

	Cursor Widget::cursor() const {
		return mCursor;
	}
	void Widget::setCursor(Cursor cur) {
		mCursor = cur;
		if (layout()->mousedownWidget == this)
			useCursor();
	}

	sf::RenderWindow& Widget::canvas() {
		return layout()->view;
	}

	void Widget::update() {
		pLayout->update();
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

		double w = width$ / 100 * parent()->computedRect().width() + width * layout()->scale;
		double h = height$ / 100 * parent()->computedRect().height() + height * layout()->scale;

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
		crect.left += x * layout()->scale + parent()->computedRect().left;
		crect.top += y * layout()->scale + parent()->computedRect().top;
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

	bool compareZIndex(Widget* i1, Widget* i2) {
		return (i1->zIndex > i2->zIndex);
	}

	bool compareZIndex_firstly_low(Widget* i1, Widget* i2) {
		return (i1->zIndex < i2->zIndex);
	}

	Widget* Widget::getMouseTargetObject(unsigned int mx, unsigned int my)
	{
		if (!isVisible())
			return 0;

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
		// white line fix
		if (computedRect().width() > canvas().getSize().x - 3)
			computedRect().right += 1;
		if (computedRect().bottom > canvas().getSize().y - 3)
			computedRect().bottom += 2;

		sf::RectangleShape wrect(sf::Vector2f(computedRect().width(), computedRect().height()));

		wrect.setPosition(computedRect().left, computedRect().top);
		wrect.setFillColor(sf::Color(0, 0, 255, 40));
		canvas().draw(wrect);

		drawChilds();
	}

	void Widget::drawChilds()
	{
		std::vector<Widget*> sequence = childs;
		std::sort(sequence.begin(), sequence.end(), compareZIndex_firstly_low);

		for (size_t i = 0; i < sequence.size(); i++)
		{
			if(sequence[i]->isVisible())
				sequence[i]->draw();
		}
	}

	Widget::Widget(Layout* aLayout, Widget* aParent, unsigned long aId)
		: pLayout(aLayout), pParent(aParent), mComputedRect(),
		visible(true), focusPolicy(AutoFocus),
		id(aId), position(TopLeft), height$(0), width$(0), x(0), y(0), zIndex(0), width(0), height(0),

		onclick(this),
		onrightclick(this),
		onmousedown(this),
		onmousemove(this),
		onmouseenter(this),
		onmouseleave(this),
		onmouseup(this),
		onfocus(this),
		onblur(this),
		onshow(this),
		onhide(this),
		onkeydown(this),
		onkeyup(this)
	{
		if (id == AutoId)
			id = rand();

		layout()->registerWidget(this);
	}

	Widget::~Widget() {
		layout()->unregisterWidget(this);
		for (size_t i = 0; i < childs.size(); i++)
			delete childs[i];

		if (layout()->mousedownWidget == this)
			layout()->mousedownWidget = 0;

		if (layout()->mousemoveWidget == this)
			layout()->mousemoveWidget = 0;

		if (!isRoot()) {
			for (size_t i = 0; i < parent()->childs.size(); i++)
			{
				if (parent()->childs[i] == this) {
					parent()->childs.erase(parent()->childs.begin() + i);
					break;
				}
			}
		}
		layout()->update();

		for (size_t i = 0; i < dependency.size(); i++)
			delete dependency[i];
	}

	Widget& Widget::operator[](size_t index) {
		return *childs[index];
	}


	void Widget::remove() {
		if (isRoot())
			return;
		delete this;
	}

	ValueAnimation Widget::createValueAnimation(Seconds duration) {
		ValueAnimation animation = *new ValueAnimation_(duration);
		dependency.push_back(&animation);
		return animation;
	}

	void Widget::hide() {
		visible = false;
		onhide.dispatch();
		layout()->update();
	}
	void Widget::show() {
		visible = true;
		onshow.dispatch();
		layout()->update();
	}

	void Widget::toggleVisibility()
	{
		visible = !visible;
	}

	bool Widget::isVisible() const {
		return visible;
	}

	bool Widget::isFocused() {
		return focusPolicy == AlwaysFocus ? true : layout()->focusedWidget == this;
	}

	void Widget::focus()
	{
		if (focusPolicy == NoFocus || focusPolicy == AlwaysFocus)
			return;

		if (isFocused())
			return;

		if (layout()->focusedWidget != 0)
			layout()->focusedWidget->onblur.dispatch();
		layout()->focusedWidget = this;
		onfocus.dispatch();
	}

	void Widget::blur()
	{
		if (focusPolicy == AlwaysFocus)
			return;

		if (!isFocused())
			return;
		layout()->focusedWidget = 0;
		onblur.dispatch();
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
		self.remove();
	}
}
