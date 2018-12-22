#pragma once

#include "Widget.h"

namespace Magenta
{
	class WindowCaption_ : public Widget {
	public:
		WindowCaption_(Layout* aLayout, Widget* aParent, unsigned long aId = AutoId);

		void draw() override;
	};
	typedef WindowCaption_& WindowCaption;

	WindowCaption createWindowCaption(Widget& owner, unsigned long aId = AutoId);
}
