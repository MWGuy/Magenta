#include "TabRegion.h"

namespace Magenta
{
	void tabregion_onmousedown(Widget& self) {
		self.layout()->getWindow()->setTransform(Moving);
	}

	TabRegion_::TabRegion_(Layout* aLayout, Widget* aParent, unsigned long aId)
		: Widget(aLayout, aParent, aId)
	{
		onmousedown.setWidgetSpecific(tabregion_onmousedown);
	}

	void TabRegion_::draw()
	{
		//drawChilds();
	}

	TabRegion createTabRegion(Widget& owner, unsigned long aId) {
		owner.childs.push_back(new TabRegion_(owner.layout(), &owner, aId));
		return (TabRegion)*owner.childs[owner.childs.size() - 1];
	}
}
