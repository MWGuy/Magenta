#include "WindowCaption.h"

namespace Magenta
{
	void dragWindow(Widget& self) {
		self.layout()->getWindow()->setTransform(Moving);
	}

	WindowCaptionInner_::WindowCaptionInner_(Layout* aLayout, Widget* aParent, unsigned long aId)
		: Widget(aLayout, aParent, aId)
	{
		onmousedown.setWidgetSpecific(dragWindow);
	}

	void WindowCaptionInner_::draw() {
		drawChilds();
	}

	WindowCaptionInner createWindowCaptionInner(Widget& owner, unsigned long aId) {
		owner.childs.push_back(new WindowCaptionInner_(owner.layout(), &owner, aId));
		return (WindowCaptionInner)*owner.childs[owner.childs.size() - 1];
	}

	WindowCaption_::WindowCaption_(Layout* aLayout, Widget* aParent, unsigned long aId)
		: Widget(aLayout, aParent, aId)
	{
		tile.loadFromFile("resources/window_caption.png");
	}

	void WindowCaption_::draw() 
	{
		if (computedRect().width() > canvas().getSize().x - 3)
			computedRect().right += 1; // white line fix

		sf::RectangleShape wrect(sf::Vector2f(computedRect().width(), computedRect().height()));
		wrect.setPosition(computedRect().left, computedRect().top);
		wrect.setTexture(&tile);
		canvas().draw(wrect);

		drawChilds();
	}

	WindowCaption createWindowCaption(Widget& owner, unsigned long aId) {
		owner.childs.push_back(new WindowCaption_(owner.layout(), &owner, aId));
		return (WindowCaption)*owner.childs[owner.childs.size() - 1];
	}
}
