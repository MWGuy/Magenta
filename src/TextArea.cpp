#include "TextArea.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace Magenta
{
	CursorPoint::CursorPoint(size_t aX, size_t aY) : x(aX), y(aY)
	{
	}

	CursorPoint::CursorPoint() : x(-1), y(-1)
	{
	}

	bool CursorPoint::isUnset() {
		return x == -1 ? y == -1 : false;
	}

	TextArea_::Glyph::Glyph(double aX, double aY, size_t aIndex) : x(aX), y(aY), index(aIndex)
	{
	}

	TextArea_::Glyph::Glyph() : x(0), y(0), index(-1)
	{
	}

	void TextArea_::processText()
	{
		if (!multiline)
			return;

		std::string reference = gtext.getString();

		size_t indexOfLineEnd = reference.find(LineEnd);

		if (indexOfLineEnd != std::string::npos) {
			reference = reference.substr(0, indexOfLineEnd);
			gtext.setString(reference);
		}
	}

	TextArea_::Glyph TextArea_::getGlyph(CursorPoint point)
	{
		bool  isBold = gtext.getStyle() == sf::Text::Bold;
		double lineSpacing = gtext.getLineSpacing() + gtext.getCharacterSize();

		double x, y;
		x = computedRect().left;
		y = computedRect().top;

		std::string reference = gtext.getString();
		sf::Uint32 previousSign = 0;

		std::size_t i = 0;
		for (;i < reference.size(); ++i)
		{
			sf::Uint32 sign = reference[i];
			previousSign = sign;

			x += font->getKerning(previousSign, sign, gtext.getCharacterSize());

			if (sign == LineEnd)
			{
				if (point.y >= y && point.y < y + lineSpacing)
				{
					if (point.x >= x && point.x < computedRect().right)
						return Glyph(x, y, i);
				}
				x = computedRect().left;
				y += lineSpacing;
				continue;
			}

			double glyphWidth = font->getGlyph(sign, gtext.getCharacterSize(), isBold).advance;

			if (point.x >= x && point.x < x + glyphWidth)
			{
				if (point.y >= y && point.y < y + lineSpacing)
					return Glyph(x, y, i);
			}
			x += glyphWidth;
		}
		return Glyph(x, y, i + 1);
	}

	void TextArea_select(Widget& self)
	{
		TextArea ta = (TextArea)self;
#ifdef _WIN32
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(self.layout()->getWindow()->handler(), &p);
		ta.select(CursorPoint(p.x, p.y));
#endif
		ta.clicked();
	}

	void TextArea_::initialize()
	{
		if (font == 0)
			font = &layout()->font;

		gtext.setColor(sf::Color::Black);
		gtext.setCharacterSize(24);

		cursorAnimation.append(AnimatedValue(cursorOpacity, 255, 0, 0.25, 0.25));
		cursorAnimation.direction = ForwardReverse;
		cursorAnimation.repeat = true;
		cursorAnimation.play();

		onmousedown = TextArea_select;
	}

	TextArea_::TextArea_(Layout* aLayout, Widget* aParent, unsigned long aId, size_t aFontSize, bool aMultiline, sf::Font* aFont)
		: Widget(aLayout, aParent, aId), font(aFont), multiline(aMultiline), selectionStart(0, 0, 0), selectionEnd(),
		cursorOpacity(1.0), cursorAnimation(0.75), fontSize(aFontSize)
	{
		initialize();
	}

	TextArea_::TextArea_(Layout* aLayout, Widget* aParent, size_t aFontSize, bool aMultiline, sf::Font* aFont)
		: Widget(aLayout, aParent, AutoId), font(aFont), multiline(aMultiline), selectionStart(0, 0, 0), selectionEnd(),
		cursorOpacity(1.0), cursorAnimation(0.75), fontSize(aFontSize)
	{
		initialize();
	}

	void TextArea_::select(CursorPoint start, CursorPoint end)
	{
		selectionStart = getGlyph(start);

		if (end.isUnset())
			return;

		selectionEnd = getGlyph(end);
	}

	bool TextArea_::isMultiline() const {
		return multiline;
	}

	void TextArea_::setMultiline(bool aMultiline) {
		multiline = aMultiline;
		if (multiline)
			processText();
	}

	void TextArea_::setText(std::string string) {
		gtext.setString(string);
		if (multiline)
			processText();
	}

	std::string TextArea_::text() {
		return gtext.getString();
	}

	void TextArea_::draw()
	{
		gtext.setCharacterSize(fontSize);
		gtext.setPosition(computedRect().left, computedRect().top);
		gtext.setFont(*font);

		canvas().draw(gtext);

		if (isFocused())
		{
			sf::RectangleShape cursor(sf::Vector2f(1, gtext.getCharacterSize() + 4));
			cursor.setPosition(selectionStart.x, selectionStart.y + gtext.getCharacterSize() / 8 - 2);
			sf::Uint8 opacity = cursorOpacity;
			cursor.setFillColor(sf::Color(0, 0, 0, opacity));
			canvas().draw(cursor);
		}

#ifdef debug
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(layout()->getWindow()->handler(), &p);
		sf::Text d("[TextArea debug]\nx: " + std::to_string(p.x) + ", y: " + std::to_string(p.y) + ", clicked: "
			+ std::to_string(clickedTimes) + " times", *font);
		d.setColor(sf::Color::Black);
		d.setCharacterSize(12);
		canvas().draw(d);
#endif debug

		drawChilds();
	}

	void TextArea_::clicked()
	{
		cursorAnimation.direction = ForwardReverse;
		cursorAnimation.toStart();
		clickedTimes++;
	}

	TextArea createTextArea(Widget& owner, unsigned long aId) {
		owner.childs.push_back(new TextArea_(owner.layout(), &owner, aId));
		return (TextArea)*owner.childs[owner.childs.size() - 1];
	}
}
