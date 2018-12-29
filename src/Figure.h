#pragma once

#include "SFML/Graphics.hpp"
#include "Widget.h"
#include <string>

namespace Magenta
{
	typedef enum {
		None,
		Raster
	} FigureType;

	class Figure
	{
		sf::RectangleShape visual;
		sf::Texture texture;
		FigureType mType;
	public:
		Figure(std::string url, size_t offsetX, size_t offsetY, size_t width, size_t height);
		Figure(std::string url);
		Figure();

		void set(std::string url, size_t offsetX, size_t offsetY, size_t width, size_t height);
		void set(std::string url);
		void clear();

		sf::RectangleShape& shape();

		double scale;

		FigureType type() const;

		void draw(Layout* layout, Rect& rect);
	};
}
