#include "ActionButton.h"

namespace Magenta
{
	void MEnter(Widget& self) {
		ActionButton& ab = (ActionButton&)self;
		ab.isMouseEntered = true;
		ab.state = 1;
		ab.update();
	}

	void MLeave(Widget& self) {
		ActionButton& ab = (ActionButton&)self;
		ab.isMouseEntered = false;
		if(ab.state != 2)
			ab.state = 0;
		ab.update();
	}

	void MDown(Widget& self) {
		ActionButton& ab = (ActionButton&)self;
		ab.state = 2;
		ab.update();
	}

	void MUp(Widget& self) {
		ActionButton& ab = (ActionButton&)self;
		ab.state = ab.isMouseEntered ? 1 : 0;
		ab.update();
	}

	ActionButton_::ActionButton_(Layout* aLayout, Widget* aParent, unsigned long aId, Figure normal, Figure hover, Figure press)
		:Widget(aLayout, aParent, aId), callbackMouseUp(MUp, *this), isMouseEntered(false), state(0),
		figNormal(normal), figHover(hover), figPress(press)
	{
		connect();
	}

	ActionButton_::ActionButton_(Layout* aLayout, Widget* aParent, Figure normal, Figure hover, Figure press)
		: Widget(aLayout, aParent, AutoId), callbackMouseUp(MUp, *this), isMouseEntered(false), state(0),
		figNormal(normal), figHover(hover), figPress(press)
	{
		connect();
	}

	ActionButton_::~ActionButton_()
	{
		layout()->onmouseup -= &callbackMouseUp;
	}

	void ActionButton_::draw()
	{
		switch (state)
		{
		case 0: // normal
			figNormal.draw(layout(), computedRect());
			break;
		case 1: // hover
			if(figHover.type() == FigureType::None)
				figNormal.draw(layout(), computedRect());
			else
			{
				figHover.draw(layout(), computedRect());
			}
			break;
		case 2: // press
			if (figPress.type() == FigureType::None)
				figNormal.draw(layout(), computedRect());
			else
			{
				figPress.draw(layout(), computedRect());
			}
			break;
		default:
			break;
		}
		drawChilds();
	}

	void ActionButton_::connect()
	{
		onmouseenter.setWidgetSpecific(MEnter);
		onmouseleave.setWidgetSpecific(MLeave);
		onmousedown.setWidgetSpecific(MDown);
		layout()->onmouseup += &callbackMouseUp;
	}

	ActionButton createActionButton(Widget& owner, unsigned long aId, Figure normal, Figure hover, Figure press) {
		owner.childs.push_back(new ActionButton_(owner.layout(), &owner, aId, normal, hover, press));
		return (ActionButton)*owner.childs[owner.childs.size() - 1];
	}
	ActionButton createActionButton(Widget& owner, Figure normal, Figure hover, Figure press) {
		owner.childs.push_back(new ActionButton_(owner.layout(), &owner, AutoId, normal, hover, press));
		return (ActionButton)*owner.childs[owner.childs.size() - 1];
	}
}
