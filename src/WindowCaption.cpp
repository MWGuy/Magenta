#include "WindowCaption.h"

namespace Magenta
{
	WindowCaption_::WindowCaption_(Layout* aLayout, Widget* aParent, unsigned long aId)
		: Widget(aLayout, aParent, aId)
	{
	}

	WindowCaption createWindowCaption(Widget& owner, unsigned long aId) {
		owner.childs.push_back(new WindowCaption_(owner.layout(), &owner, aId));
		return (WindowCaption)*owner.childs[owner.childs.size() - 1];
	}
}
