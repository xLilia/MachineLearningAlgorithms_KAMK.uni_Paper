#include "dataPoint.h"



dataPoint::dataPoint(sf::Vector2f coords)
{
	Point.setFillColor(sf::Color::White);
	Point.setRadius(5);
	Point.setPosition(coords);
}


dataPoint::~dataPoint()
{
}
