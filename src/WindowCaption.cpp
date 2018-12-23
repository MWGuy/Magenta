#include "WindowCaption.h"

namespace Magenta
{
	void dragWindow(Widget& self) {
		self.layout()->getWindow()->setTransform(Moving);
	}

	WindowCaption_::WindowCaption_(Layout* aLayout, Widget* aParent, unsigned long aId)
		: Widget(aLayout, aParent, aId)
	{
		onmousedown.setWidgetSpecific(dragWindow);
	}

	void WindowCaption_::draw() 
	{
		sf::RectangleShape wrect(sf::Vector2f(computedRect().width(), computedRect().height()));
		wrect.setPosition(computedRect().left, computedRect().top);
		wrect.setFillColor(sf::Color(255, 0, 0, 40));
		canvas().draw(wrect);

		drawChilds();
	}

	WindowCaption createWindowCaption(Widget& owner, unsigned long aId) {
		owner.childs.push_back(new WindowCaption_(owner.layout(), &owner, aId));
		return (WindowCaption)*owner.childs[owner.childs.size() - 1];
	}
}
