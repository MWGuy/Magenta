#pragma once

#include "TextArea.h"

namespace Magenta
{
	class AddressText_ : public TextArea_ {
	public:
		AddressText_(Layout* aLayout, Widget* aParent, unsigned long aId = AutoId);

		void draw() override;
	};
	typedef AddressText_& AddressText;

	AddressText createAddressText(Widget& owner, unsigned long aId = AutoId);
}
