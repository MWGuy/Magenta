#include "Rect.h"

namespace Magenta
{
	void Rect::setHeight(double len) {
		bottom = top + len;
	}

	void Rect::setWidth(double len) {
		right = left + len;
	}

	double Rect::height() {
		return bottom - top;
	}

	double Rect::width() {
		return right - left;
	}

	Rect::Rect(double aLeft, double aTop, double aRight, double aBottom)
		: left(aLeft), top(aTop), right(aRight), bottom(aBottom)
	{
	}

	Rect::Rect() : left(0), top(0), right(0), bottom(0)
	{
	}
}
