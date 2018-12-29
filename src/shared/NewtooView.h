#pragma once

#include "SFML/Graphics.hpp"
#include "../Widget.h"

namespace Newtoo {
	class View;
}

namespace Magenta
{
	class NewtooView_ : public Widget {
	public:
		NewtooView_(Layout* aLayout, Widget* aParent, unsigned long aId = AutoId);

		void draw() override;
	};
	typedef NewtooView_& NewtooView;

	NewtooView createNewtooView(Widget& owner, unsigned long aId = AutoId);

}
