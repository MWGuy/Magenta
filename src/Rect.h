#pragma once

namespace Magenta
{
	struct Rect {
		unsigned int left, top, right, bottom;

		// ������� ���������� ``left`` � ``top``
		void setHeight(double len);
		void setWidth(double len);

		double height();
		double width();

		Rect(double aLeft, double aTop, double aRight, double aBottom);
		Rect();
	};
}
