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
		return right - left;
	}

	unsigned int Rect::width() {
		return bottom - top;
	}
}
