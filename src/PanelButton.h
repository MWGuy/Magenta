#pragma once

#include "ValueAnimation.h"
#include "Figure.h"

namespace Magenta
{
	class PanelButton_ : public Widget {
		SharedEventCallback callbackMouseUp;
	public:
		PanelButton_(Layout* aLayout, Widget* aParent, unsigned long aId = AutoId, Figure fig = Figure());
		PanelButton_(Layout* aLayout, Widget* aParent, Figure fig = Figure());

		~PanelButton_() override;

		ValueAnimation_ animation;
		short state;

		void draw() override;

		Figure figure;

		bool isMouseEntered;

	private:
		void setupAnimation();
		void connect();
	};
	typedef PanelButton_& PanelButton;

	PanelButton createPanelButton(Widget& owner, unsigned long aId = AutoId, Figure fig = Figure());
	PanelButton createPanelButton(Widget& owner, Figure fig = Figure());
}
