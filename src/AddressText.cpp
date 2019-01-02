#include "AddressText.h"

namespace Magenta
{
	AddressText_::AddressText_(Layout* aLayout, Widget* aParent, unsigned long aId) : TextArea_(aLayout, aParent, aId, 13, false)
	{
		// on focus
		// on blur
	}

	AddressText createAddressText(Widget& owner, unsigned long aId) {
		owner.childs.push_back(new AddressText_(owner.layout(), &owner, aId));
		return (AddressText)*owner.childs[owner.childs.size() - 1];
	}
}
