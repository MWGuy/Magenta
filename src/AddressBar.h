#pragma once

#include "SFML/Graphics.hpp"
#include "Widget.h"

namespace Magenta
{
	class AddressBar_ : public Widget {
	public:
		AddressBar_(Layout* aLayout, Widget* aParent, unsigned long aId = AutoId);

		void draw() override;
	};
	typedef AddressBar_& AddressBar;

	AddressBar createAddressBar(Widget& owner, unsigned long aId = AutoId);
}
