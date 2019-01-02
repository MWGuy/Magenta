#include "AddressBar.h"

#define CORNER_RADIUS 8
#define INNER_CORNER_RADIUS 7
#define OUTLINE_COLOR 130, 200, 247
#define OUTLINE_WIDTH 1
#define INNER_COLOR 244, 244, 244

namespace Magenta
{
	AddressBar_::AddressBar_(Layout* aLayout, Widget* aParent, unsigned long aId) : Widget(aLayout, aParent, aId)
	{
	}

	void AddressBar_::draw()
	{
		sf::CircleShape outlineTopLeft(CORNER_RADIUS);
		outlineTopLeft.setFillColor(sf::Color(OUTLINE_COLOR));
		outlineTopLeft.setPosition(computedRect().left, computedRect().top);
		canvas().draw(outlineTopLeft);
		sf::CircleShape outlineTopBottom(CORNER_RADIUS);
		outlineTopBottom.setFillColor(sf::Color(OUTLINE_COLOR));
		outlineTopBottom.setPosition(computedRect().left, computedRect().bottom - CORNER_RADIUS*2);
		canvas().draw(outlineTopBottom);
		sf::CircleShape outlineRightLeft(CORNER_RADIUS);
		outlineRightLeft.setFillColor(sf::Color(OUTLINE_COLOR));
		outlineRightLeft.setPosition(computedRect().right - CORNER_RADIUS * 2, computedRect().top);
		canvas().draw(outlineRightLeft);
		sf::CircleShape outlineRightBottom(CORNER_RADIUS);
		outlineRightBottom.setFillColor(sf::Color(OUTLINE_COLOR));
		outlineRightBottom.setPosition(computedRect().right - CORNER_RADIUS * 2, computedRect().bottom - CORNER_RADIUS * 2);
		canvas().draw(outlineRightBottom);

		sf::RectangleShape outlineRectV(sf::Vector2f(computedRect().width() - CORNER_RADIUS*2, computedRect().height()));
		outlineRectV.setPosition(computedRect().left + CORNER_RADIUS, computedRect().top);
		outlineRectV.setFillColor(sf::Color(OUTLINE_COLOR));
		canvas().draw(outlineRectV);
		sf::RectangleShape outlineRectH(sf::Vector2f(computedRect().width(), computedRect().height() - CORNER_RADIUS * 2));
		outlineRectH.setPosition(computedRect().left, computedRect().top + CORNER_RADIUS);
		outlineRectH.setFillColor(sf::Color(OUTLINE_COLOR));
		canvas().draw(outlineRectH);

		sf::CircleShape innerTopLeft(INNER_CORNER_RADIUS);
		innerTopLeft.setFillColor(sf::Color(INNER_COLOR));
		innerTopLeft.setPosition(computedRect().left + OUTLINE_WIDTH, computedRect().top + OUTLINE_WIDTH);
		canvas().draw(innerTopLeft);
		sf::CircleShape innerTopBottom(INNER_CORNER_RADIUS);
		innerTopBottom.setFillColor(sf::Color(INNER_COLOR));
		innerTopBottom.setPosition(computedRect().left + OUTLINE_WIDTH,
			computedRect().bottom - INNER_CORNER_RADIUS * 2 - OUTLINE_WIDTH);
		canvas().draw(innerTopBottom);
		sf::CircleShape innerRightLeft(INNER_CORNER_RADIUS);
		innerRightLeft.setFillColor(sf::Color(INNER_COLOR));
		innerRightLeft.setPosition(computedRect().right - INNER_CORNER_RADIUS * 2 - OUTLINE_WIDTH,
			computedRect().top + OUTLINE_WIDTH);
		canvas().draw(innerRightLeft);
		sf::CircleShape innerRightBottom(INNER_CORNER_RADIUS);
		innerRightBottom.setFillColor(sf::Color(INNER_COLOR));
		innerRightBottom.setPosition(computedRect().right - INNER_CORNER_RADIUS * 2 - OUTLINE_WIDTH,
			computedRect().bottom - INNER_CORNER_RADIUS * 2 - OUTLINE_WIDTH);
		canvas().draw(innerRightBottom);

		sf::RectangleShape innerRectV(sf::Vector2f(computedRect().width() - INNER_CORNER_RADIUS * 2,
			computedRect().height() - OUTLINE_WIDTH * 2));
		innerRectV.setPosition(computedRect().left + INNER_CORNER_RADIUS, computedRect().top + OUTLINE_WIDTH);
		innerRectV.setFillColor(sf::Color(INNER_COLOR));
		canvas().draw(innerRectV);
		sf::RectangleShape innerRectH(sf::Vector2f(computedRect().width() - OUTLINE_WIDTH * 2,
			computedRect().height() - INNER_CORNER_RADIUS * 2));
		innerRectH.setPosition(computedRect().left + OUTLINE_WIDTH, computedRect().top + INNER_CORNER_RADIUS);
		innerRectH.setFillColor(sf::Color(INNER_COLOR));
		canvas().draw(innerRectH);

		drawChilds();
	}

	AddressBar createAddressBar(Widget& owner, unsigned long aId) {
		owner.childs.push_back(new AddressBar_(owner.layout(), &owner, aId));
		return (AddressBar)*owner.childs[owner.childs.size() - 1];
	}
}
