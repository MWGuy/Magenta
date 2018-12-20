#pragma once

namespace Magenta
{
	struct Rect {
		unsigned int left, top, right, bottom;

		// ������� ���������� ``left`` � ``top``
		void setHeight(unsigned int len);
		void setWidth(unsigned int len);

		unsigned int height();
		unsigned int width();

		Rect(unsigned int aLeft, unsigned int aTop, unsigned int aRight, unsigned int aBottom);
		Rect();
	};
}
