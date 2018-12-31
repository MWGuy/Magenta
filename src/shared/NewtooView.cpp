#include "NewtooView.h"

namespace Magenta
{
	NewtooView_::NewtooView_(Layout* aLayout, Widget* aParent, unsigned long aId)
		: Widget(aLayout, aParent, aId)
	{
	}

	void NewtooView_::draw() {
		if (computedRect().width() > canvas().getSize().x - 3)
			computedRect().right += 1; // white line fix

		sf::RectangleShape wrect(sf::Vector2f(computedRect().width(), computedRect().height()));
		wrect.setPosition(computedRect().left, computedRect().top);
		wrect.setFillColor(sf::Color(255, 255, 255));
		canvas().draw(wrect);

		sf::RectangleShape panelBorder(sf::Vector2f(computedRect().width(), 1));
		panelBorder.setPosition(0, computedRect().top + 34 * layout()->scale);
		panelBorder.setFillColor(sf::Color(226, 226, 226));
		canvas().draw(panelBorder);

		drawChilds();
	}

	NewtooView createNewtooView(Widget& owner, unsigned long aId) {
		owner.childs.push_back(new NewtooView_(owner.layout(), &owner, aId));
		return (NewtooView)*owner.childs[owner.childs.size() - 1];
	}
}
