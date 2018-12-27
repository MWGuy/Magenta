#pragma once

#include "Figure.h"

namespace Magenta
{
	class ActionButton_ : public Widget {
		GlobalEventCallback callbackMouseUp;
	public:
		ActionButton_(Layout* aLayout, Widget* aParent, unsigned long aId = AutoId,
			Figure normal = Figure(), Figure hover = Figure(), Figure press = Figure());
		ActionButton_(Layout* aLayout, Widget* aParent, Figure normal = Figure(),
			Figure hover = Figure(), Figure press = Figure());

		ActionButton_::~ActionButton_();

		short state;

		void draw() override;

		Figure figNormal;
		Figure figHover;
		Figure figPress;

		bool isMouseEntered;

	private:

		void connect();
	};
	typedef ActionButton_& ActionButton;

	ActionButton createActionButton(Widget& owner, unsigned long aId = AutoId,
		Figure normal = Figure(), Figure hover = Figure(), Figure press = Figure());
	ActionButton createActionButton(Widget& owner, Figure normal = Figure(), Figure hover = Figure(), Figure press = Figure());
}
