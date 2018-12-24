#pragma once

#include "WindowCaption.h"

namespace Magenta
{
	class TabRegion_ : public Widget {
	public:
		TabRegion_(Layout* aLayout, Widget* aParent, unsigned long aId = AutoId);

		void draw() override;
	};
	typedef TabRegion_& TabRegion;

	TabRegion createTabRegion(Widget& owner, unsigned long aId = AutoId);
}
