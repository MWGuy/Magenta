#pragma once

namespace Magenta
{
	struct Rect {
		unsigned int left, top, right, bottom;

		// Сначала установите ``left`` и ``top``
		void setHeight(unsigned int len);
		void setWidth(unsigned int len);

		unsigned int height();
		unsigned int width();
	};
}
