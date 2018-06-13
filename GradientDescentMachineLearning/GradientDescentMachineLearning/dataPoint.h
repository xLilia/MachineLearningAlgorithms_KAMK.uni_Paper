#pragma once
#include <SFML\Graphics.hpp>

class dataPoint
{
public:
	dataPoint(sf::Vector2f coords);
	sf::CircleShape Point;
	~dataPoint();
};

