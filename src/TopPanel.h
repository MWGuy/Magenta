#pragma once

#include "SFML/Graphics.hpp"
#include "Widget.h"

namespace Magenta
{
	class TopPanel_ : public Widget {
	public:
		TopPanel_(Layout* aLayout, Widget* aParent, unsigned long aId = AutoId);

		void draw() override;
	};
	typedef TopPanel_& TopPanel;

	TopPanel createTopPanel(Widget& owner, unsigned long aId = AutoId);
}
