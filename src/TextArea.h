#pragma once

#include "SFML/Graphics.hpp"
#include "Widget.h"

#define LineEnd '\n'

namespace Magenta
{
	struct CursorPoint {
		size_t x, y;
		CursorPoint(size_t aX, size_t aY);
		CursorPoint();

		bool isUnset();
	};

	class TextArea_ : public Widget {
		sf::Font* font;
		sf::Text gtext;
		bool multiline;

		void processText();

	public:
		struct Glyph {
			double x, y;
			size_t index;

			Glyph(double aX, double aY, size_t aIndex);
			Glyph();
		};

	protected:
		Glyph selectionStart;
		Glyph selectionEnd;

		double cursorOpacity;
		ValueAnimation_ cursorAnimation;

		Glyph getGlyph(CursorPoint point);
		void initialize();

	public:
		TextArea_(Layout* aLayout, Widget* aParent, unsigned long aId = AutoId, size_t aFontSize = 12,
			bool aMultiline = true, sf::Font* aFont = 0);
		TextArea_(Layout* aLayout, Widget* aParent, size_t aFontSize = 12, bool aMultiline = true, sf::Font* aFont = 0);

		void select(CursorPoint start, CursorPoint end = CursorPoint());

		bool isMultiline() const;
		void setMultiline(bool aMultiline);

		void setText(std::string string);
		std::string text();

		size_t fontSize;

		void draw() override;

		void clicked();

		unsigned int clickedTimes = 0;
	};
	typedef TextArea_& TextArea;

	TextArea createTextArea(Widget& owner, unsigned long aId = AutoId);
}
