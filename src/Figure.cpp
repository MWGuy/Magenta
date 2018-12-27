#include "Figure.h"

namespace Magenta
{
	Figure::Figure(std::string url, size_t offsetX, size_t offsetY, size_t width, size_t height)
		: mType(FigureType::None)
	{
		visual.setOrigin(sf::Vector2f(0, 0));
		set(url, offsetX, offsetY, width, height);
	}
	Figure::Figure(std::string url) : mType(FigureType::None)
	{
		visual.setOrigin(sf::Vector2f(0, 0));
		set(url);
	}
	Figure::Figure() : mType(FigureType::None)
	{
		visual.setOrigin(sf::Vector2f(0, 0));
	}

	void Figure::set(std::string url, size_t offsetX, size_t offsetY, size_t width, size_t height)
	{
		if (texture.loadFromFile(url, sf::IntRect(offsetX, offsetY, width, height)))
		{
			mType = FigureType::Raster;
		}
	}

	void Figure::set(std::string url)
	{
		if (texture.loadFromFile(url)) {
			mType = FigureType::Raster;
		}
	}

	void Figure::clear()
	{
		mType = FigureType::None;
	}

	FigureType Figure::type() const {
		return mType;
	}

	void Figure::draw(Layout* layout, Rect& rect)
	{
		switch (mType)
		{
		case Raster:
			visual.setPosition(rect.left, rect.top);
			visual.setTexture(texture);
			layout->view.draw(visual);
			break;
		case None:
			break;
		}
	}
}
