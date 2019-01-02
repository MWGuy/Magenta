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

	FontColor::FontColor(unsigned char aRed, unsigned char aGreen, unsigned char aBlue, unsigned char aAlpha)
		:red(aRed), green(aGreen), blue(aBlue), alpha(aAlpha)
	{
	}

	TextArea_::Glyph::Glyph(double aX, double aY, size_t aIndex) : x(aX), y(aY), index(aIndex)
	{
	}

	TextArea_::Glyph::Glyph() : x(0), y(0), index(-1)
	{
	}

	void TextArea_::processText()
	{
		if (multiline)
			return;

		std::string reference = gtext.getString();

		size_t indexOfLineEnd = reference.find(LineEnd);

		if (indexOfLineEnd != std::string::npos) {
			reference = reference.substr(0, indexOfLineEnd);
		}
		reference += LineEnd;

		gtext.setString(reference);
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

#define AddLine() \
if(isMultiline()) { \
selectionBoxes.push_back(sf::RectangleShape(sf::Vector2f(0.0, lineSpacing ))); \
selectionBoxes.back().setPosition(x, y + (int)(lineSpacing / 8)); \
selectionBoxes.back().setFillColor(sf::Color(SELECTION_COLOR)); \
} else {\
selectionBoxes.push_back(sf::RectangleShape(sf::Vector2f(0.0, lineSpacing + (int)(lineSpacing / 4) ))); \
selectionBoxes.back().setPosition(x, y); selectionBoxes.back().setFillColor(sf::Color(SELECTION_COLOR)); }

#define GrowLine(len) selectionBoxes.back().setSize(sf::Vector2f(selectionBoxes.back().getSize().x + len, \
selectionBoxes.back().getSize().y))
#define ThisLine() selectionBoxes.back()

	void TextArea_::computeSelectionVisual()
	{
		Glyph *start, *end;

		if (selectionStart.index < selectionEnd.index)
		{
			start = &selectionStart;
			end = &selectionEnd;
		} else
		{
			start = &selectionEnd;
			end = &selectionStart;
		}

		bool  isBold = gtext.getStyle() == sf::Text::Bold;
		double lineSpacing = gtext.getLineSpacing() + gtext.getCharacterSize();

		double x, y;
		x = start->x;
		y = start->y;

		std::string reference = gtext.getString();

		AddLine();

		size_t end_index = end->index - 1;
		if (end_index == reference.size())
			end_index--;

		for (std::size_t i = start->index; i <= end_index; ++i)
		{
			sf::Uint32 sign = reference[i];
			sf::Uint32 previousSign = i > 0 ? reference[i - 1] : 0;

			double cx = x;

			x += font->getKerning(previousSign, sign, gtext.getCharacterSize());

			if (sign == LineEnd)
			{
				x = computedRect().left;
				y += lineSpacing;
				AddLine();
				continue;
			}
			x += font->getGlyph(sign, gtext.getCharacterSize(), isBold).advance;

			GrowLine(x - cx);
		}
	}

	void TextArea_mousedown(Widget& self)
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

	void TextArea_mousemove(Widget& self)
	{
		if (self.layout()->mousedownWidget != &self)
			return;
		TextArea ta = (TextArea)self;
#ifdef _WIN32
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(self.layout()->getWindow()->handler(), &p);
		ta.select(CursorPoint(ta.selectionStart.x, ta.selectionStart.y), CursorPoint(p.x, p.y));
#endif
	}

	void TextArea_blur(Widget& self)
	{
		TextArea ta = (TextArea)self;
		ta.clearSelection();
	}

	void TextArea_keydown(Widget& self, KeyCode key)
	{
		char character = keyCodeToCharacter(key, self.layout()->getWindow());
		if (character != NotCharacterKey)
		{
			TextArea ta = (TextArea)self;
			ta.setText(ta.text() + character);
		}
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

		onmousemove.setWidgetSpecific(TextArea_mousemove);
		onmousedown.setWidgetSpecific(TextArea_mousedown);
		onblur.setWidgetSpecific(TextArea_blur);
		onkeydown.setWidgetSpecific(TextArea_keydown);
	}

	TextArea_::TextArea_(Layout* aLayout, Widget* aParent, unsigned long aId, FontSize aFontSize, FontColor aColor,
		bool aMultiline, bool aReadonly, bool aSelectable, sf::Font* aFont)
		: Widget(aLayout, aParent, aId), font(aFont), multiline(aMultiline), selectionStart(0, 0, 0), selectionEnd(),
		cursorOpacity(1.0), cursorAnimation(0.75), readonly(aReadonly), selectable(aSelectable),
		fontSize(aFontSize), fontColor(aColor)
	{
		initialize();
	}

	TextArea_::TextArea_(Layout* aLayout, Widget* aParent, FontSize aFontSize, FontColor aColor, bool aMultiline,
		bool aReadonly, bool aSelectable, sf::Font* aFont)
		: Widget(aLayout, aParent, AutoId), font(aFont), multiline(aMultiline), selectionStart(0, 0, 0), selectionEnd(),
		cursorOpacity(1.0), cursorAnimation(0.75), readonly(aReadonly), selectable(aSelectable),
		fontSize(aFontSize), fontColor(aColor)
	{
		initialize();
	}

	void TextArea_::select(CursorPoint point1, CursorPoint point2)
	{
		selectionBoxes.clear();
		if (!selectable)
			return;

		selectionStart = getGlyph(point1);

		if (point2.isUnset()) {
			selectionStart.index = selectionEnd.index;
		}
		else selectionEnd = getGlyph(point2);

		if (isSelected())
			computeSelectionVisual();
	}

	bool TextArea_::isSelected() {
		return selectionStart.index != selectionEnd.index;
	}

	bool TextArea_::isMultiline() const {
		return multiline;
	}

	void TextArea_::setMultiline(bool aMultiline) {
		multiline = aMultiline;
		processText();
	}

	void TextArea_::clearSelection()
	{
		std::string str = gtext.getString();
		selectionStart.index = str.size() - 1;
		selectionEnd.index = selectionStart.index;
	}

	void TextArea_::setText(std::string string) {
		gtext.setString(string);
		processText();
	}

	std::string TextArea_::text() {
		std::string str = gtext.getString();
		while (str[str.size() - 1] == LineEnd)
			str = str.erase(str.size() - 1, 1);
		return str;
	}

	void TextArea_::drawTextArea()
	{
		for (size_t i = 0; i < selectionBoxes.size(); i++)
			canvas().draw(selectionBoxes[i]);

		gtext.setCharacterSize(fontSize);
		gtext.setColor(sf::Color(fontColor.red, fontColor.green, fontColor.blue, fontColor.alpha));
		gtext.setPosition(computedRect().left, computedRect().top);
		gtext.setFont(*font);

		canvas().draw(gtext);

		if (isFocused() && !isSelected() && !readonly)
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
	}

	void TextArea_::draw()
	{
		drawTextArea();
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
