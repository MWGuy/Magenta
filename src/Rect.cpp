#include "Rect.h"

namespace Magenta
{
	void Rect::setHeight(unsigned int len) {
		bottom = top + len;
	}

	void Rect::setWidth(unsigned int len) {
		right = left + len;
	}

	unsigned int Rect::height() {
		return bottom - top;
	}

	unsigned int Rect::width() {
		return right - left;
	}

	Rect::Rect(unsigned int aLeft, unsigned int aTop, unsigned int aRight, unsigned int aBottom)
		: left(aLeft), top(aTop), right(aRight), bottom(aBottom)
	{
	}

	Rect::Rect() : left(0), top(0), right(0), bottom(0)
	{
	}
}
