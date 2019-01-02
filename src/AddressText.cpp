#include "AddressText.h"

namespace Magenta
{
	AddressText_::AddressText_(Layout* aLayout, Widget* aParent, unsigned long aId) : TextArea_(aLayout, aParent, aId, 13,
		FontColor(42, 42, 42, 255), false, false, true)
	{
		// on focus
		// on blur
	}

	void AddressText_::draw()
	{
		bool focused = isFocused();
		if (!focused)
			fontColor.alpha -= 40;

		drawTextArea();

		if (!focused)
			fontColor.alpha += 40;

		drawChilds();
	}

	AddressText createAddressText(Widget& owner, unsigned long aId) {
		owner.childs.push_back(new AddressText_(owner.layout(), &owner, aId));
		return (AddressText)*owner.childs[owner.childs.size() - 1];
	}
}
