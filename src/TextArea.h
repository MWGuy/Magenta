#pragma once

#include "SFML/Graphics.hpp"
#include "Widget.h"

#define SELECTION_COLOR 0, 114, 255, 47

#define LineEnd '\n'

namespace Magenta
{
	struct CursorPoint {
		size_t x, y;
		CursorPoint(size_t aX, size_t aY);
		CursorPoint();

		bool isUnset();
	};

	struct FontColor {
		unsigned char red, green, blue, alpha;

		FontColor(unsigned char aRed = 0, unsigned char aGreen = 0, unsigned char aBlue = 0, unsigned char aAlpha = 255);
	};

	typedef size_t FontSize;

	class TextArea_ : public Widget {
		sf::Font* font;
		sf::Text gtext;
		bool multiline;

		void processText();

	public:
		std::vector<sf::RectangleShape> selectionBoxes;
		void computeSelectionVisual();

		struct Glyph {
			double x, y;
			size_t index;

			Glyph(double aX, double aY, size_t aIndex);
			Glyph();
		};
		Glyph selectionStart;
		Glyph selectionEnd;

		Glyph getGlyph(CursorPoint point);

	protected:
		double cursorOpacity;
		ValueAnimation_ cursorAnimation;
		void initialize();

	public:
		TextArea_(Layout* aLayout, Widget* aParent, unsigned long aId = AutoId, FontSize aFontSize = 12,
			FontColor aColor = FontColor(), bool aMultiline = true, bool aReadonly = true, bool aSelectable = true,
			sf::Font* aFont = 0);
		TextArea_(Layout* aLayout, Widget* aParent, FontSize aFontSize = 12, FontColor aColor = FontColor(),
			bool aMultiline = true, bool aReadonly = true, bool aSelectable = true, sf::Font* aFont = 0);

		void select(CursorPoint point1, CursorPoint point2 = CursorPoint());

		bool isSelected();
		bool isMultiline() const;
		void setMultiline(bool aMultiline);

		void clearSelection();
		void selectAll();
		void undo();
		void redo();

		void setText(std::string string);
		std::string text();

		bool readonly;
		bool selectable;

		FontSize fontSize;
		FontColor fontColor;

		void drawTextArea();
		void draw() override;

		sf::Text& getSfText();

		void clicked();

		std::vector<std::string> toUndo;
		std::vector<std::string> toRedo;

		unsigned int clickedTimes = 0;
		bool shift = false;
		bool ctrl = false; // cmd on Mac
	};
	typedef TextArea_& TextArea;

	TextArea createTextArea(Widget& owner, unsigned long aId = AutoId);
}
