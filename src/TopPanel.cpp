#include "TopPanel.h"

#define TopPanelColor sf::Color(244, 244, 244)

namespace Magenta
{
	TopPanel_::TopPanel_(Layout* aLayout, Widget* aParent, unsigned long aId) : Widget(aLayout, aParent, aId)
	{
	}

	void TopPanel_::draw()
	{
		if (layout()->getWindow()->isMaximized())
		{
			sf::RectangleShape solid(sf::Vector2f(computedRect().width() + 1, computedRect().height()));
			solid.setFillColor(sf::Color(TopPanelColor));
			solid.setPosition(computedRect().left, computedRect().top);

			canvas().draw(solid);
		}
		else
		{
			sf::CircleShape lCorner(5.0f);
			lCorner.setFillColor(sf::Color(TopPanelColor));
			lCorner.setPosition(computedRect().left, computedRect().top);
			sf::CircleShape rCorner(5.0f);
			rCorner.setFillColor(sf::Color(TopPanelColor));
			rCorner.setPosition(computedRect().right - 9, computedRect().top);

			sf::RectangleShape solidTop(sf::Vector2f(computedRect().width() - 10, 5));
			solidTop.setFillColor(sf::Color(TopPanelColor));
			solidTop.setPosition(computedRect().left + 5, computedRect().top);
			sf::RectangleShape solidBottom(sf::Vector2f(computedRect().width() + 1, computedRect().height() - 5));
			solidBottom.setFillColor(sf::Color(TopPanelColor));
			solidBottom.setPosition(computedRect().left, computedRect().top + 5);

			canvas().draw(solidTop);
			canvas().draw(solidBottom);

			canvas().draw(lCorner);
			canvas().draw(rCorner);
		}
		drawChilds();
	}

	TopPanel createTopPanel(Widget& owner, unsigned long aId) {
		owner.childs.push_back(new TopPanel_(owner.layout(), &owner, aId));
		return (TopPanel)*owner.childs[owner.childs.size() - 1];
	}
}
