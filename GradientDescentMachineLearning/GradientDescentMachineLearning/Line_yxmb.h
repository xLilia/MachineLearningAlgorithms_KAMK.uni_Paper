#pragma once
#include <SFML\Graphics.hpp>

#include "dataPoint.h"

class Line_yxmb
{
public:
	Line_yxmb();
	Line_yxmb(float m, float b);
	float fx(float X);
	void bindToData(std::vector<dataPoint>& PointsData);
	void bindToWindow(sf::RenderWindow & rw);
	void gradientDescent(float learning_rate);
	sf::Vertex* getDrawableLine();
	sf::Vertex * mapPointsToScreen(sf::Vertex * drawableLine);
	~Line_yxmb();

	std::vector<dataPoint>* PointsData;
	float m = 0;
	float b = 0;
	sf::Vertex* linePts;
	sf::RenderWindow* rw;
};

