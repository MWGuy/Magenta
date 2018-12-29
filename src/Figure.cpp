#include "Figure.h"

namespace Magenta
{
	Figure::Figure(std::string url, size_t offsetX, size_t offsetY, size_t width, size_t height)
		: mType(FigureType::None), scale(1.0f)
	{
		texture.setRepeated(false);
		texture.setSmooth(true);
		set(url, offsetX, offsetY, width, height);
	}
	Figure::Figure(std::string url) : mType(FigureType::None), scale(1.0f)
	{
		texture.setRepeated(false);
		texture.setSmooth(true);
		set(url);
	}
	Figure::Figure() : mType(FigureType::None), scale(1.0f)
	{
		texture.setRepeated(false);
		texture.setSmooth(true);
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

	sf::RectangleShape& Figure::shape() {
		return visual;
	}

	FigureType Figure::type() const {
		return mType;
	}

	void Figure::draw(Layout* layout, Rect& rect)
	{
		switch (mType)
		{
		case Raster:
			visual.setOrigin(rect.width() / 2, rect.height() / 2);
			visual.setScale(sf::Vector2f(scale, scale));
			visual.setPosition(rect.left + visual.getOrigin().x, rect.top + visual.getOrigin().y);
			visual.setSize(sf::Vector2f(rect.width(), rect.height()));
			visual.setTexture(&texture);
			layout->view.draw(visual);
			break;
		case None:
			break;
		}
	}
}
