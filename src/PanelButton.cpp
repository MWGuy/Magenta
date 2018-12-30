#include "PanelButton.h"

namespace Magenta
{
	void PanelButton_MEnter(Widget& self) {
		PanelButton& pb = (PanelButton&)self;
		pb.isMouseEntered = true;
		pb.state = 1;
		pb.update();
		pb.animation.direction = AnimationDirection::Forward;
		pb.animation.play();
	}

	void PanelButton_MLeave(Widget& self) {
		PanelButton& pb = (PanelButton&)self;
		pb.isMouseEntered = false;
		if (pb.state != 2)
			pb.state = 0;
		pb.update();
		pb.animation.direction = AnimationDirection::Backward;
		if (pb.animation.values[0].startValue == 1.1f) {
			pb.animation.pause();
			pb.animation.values[0].startValue = 1.0f;
			pb.animation.speed = 1.75;
			if(pb.animation.position == 0)
				pb.animation.position = 0.01;
			else
				pb.animation.position = 0.1;
		}
		pb.animation.play();
	}

	void PanelButton_MDown(Widget& self) {
		PanelButton& pb = (PanelButton&)self;
		pb.state = 2;
		pb.update();
		pb.animation.values[0].startValue = 1.1f;
		pb.animation.speed = 1.8;
		pb.animation.direction = AnimationDirection::Backward;
		pb.animation.play();
	}

	void PanelButton_MUp(Widget& self) {
		PanelButton& pb = (PanelButton&)self;
		pb.state = pb.isMouseEntered ? 1 : 0;
		pb.update();
		if (pb.state == 1) {
			pb.animation.direction = AnimationDirection::Forward;
			pb.animation.play();
		}
	}

	PanelButton_::PanelButton_(Layout* aLayout, Widget* aParent, unsigned long aId, Figure fig)
		:Widget(aLayout, aParent, aId), callbackMouseUp(PanelButton_MUp, *this), isMouseEntered(false), animation(0.11),
		state(0), figure(fig)
	{
		setupAnimation();
		connect();
	}

	PanelButton_::PanelButton_(Layout* aLayout, Widget* aParent, Figure fig)
		: Widget(aLayout, aParent, AutoId), callbackMouseUp(PanelButton_MUp, *this), isMouseEntered(false), animation(0.11),
		state(0), figure(fig)
	{
		setupAnimation();
		connect();
	}

	PanelButton_::~PanelButton_()
	{
		layout()->onmouseup -= &callbackMouseUp;
	}

	void PanelButton_::draw()
	{
		figure.draw(layout(), computedRect());

		drawChilds();
	}

	void PanelButton_::setupAnimation()
	{
		animation.append(AnimatedValue(figure.scale, 1.0f, 1.19f, 0.1));
		animation.stayAtEnd = true;
		animation.speed = 1.75;
	}

	void PanelButton_::connect()
	{
		onmouseenter.setWidgetSpecific(PanelButton_MEnter);
		onmouseleave.setWidgetSpecific(PanelButton_MLeave);
		onmousedown.setWidgetSpecific(PanelButton_MDown);
		layout()->onmouseup += &callbackMouseUp;
	}

	PanelButton createPanelButton(Widget& owner, unsigned long aId, Figure fig) {
		owner.childs.push_back(new PanelButton_(owner.layout(), &owner, aId, fig));
		return (PanelButton)*owner.childs[owner.childs.size() - 1];
	}
	PanelButton createPanelButton(Widget& owner, Figure fig) {
		owner.childs.push_back(new PanelButton_(owner.layout(), &owner, AutoId, fig));
		return (PanelButton)*owner.childs[owner.childs.size() - 1];
	}
}
