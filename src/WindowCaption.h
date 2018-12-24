#pragma once

#include "SFML/Graphics.hpp"
#include "Widget.h"

namespace Magenta
{
	class WindowCaptionInner_ : public Widget {
	public:
		WindowCaptionInner_(Layout* aLayout, Widget* aParent, unsigned long aId = AutoId);

		void draw() override;
	};
	typedef WindowCaptionInner_& WindowCaptionInner;

	WindowCaptionInner createWindowCaptionInner(Widget& owner, unsigned long aId = AutoId);

	class WindowCaption_ : public Widget {
	public:
		WindowCaption_(Layout* aLayout, Widget* aParent, unsigned long aId = AutoId);

		sf::Texture tile;

		void draw() override;
	};
	typedef WindowCaption_& WindowCaption;

	WindowCaption createWindowCaption(Widget& owner, unsigned long aId = AutoId);
}
