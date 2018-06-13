#include "Line_yxmb.h"

Line_yxmb::Line_yxmb() : m(0), b(0)
{
	linePts = new sf::Vertex[2]{
		sf::Vertex(sf::Vector2f(0, fx(0))),
		sf::Vertex(sf::Vector2f(1, fx(1)))
	};
}

Line_yxmb::Line_yxmb(float m, float b) : m(m), b(b)
{

	linePts = new sf::Vertex[2]{
		sf::Vertex(sf::Vector2f(0, fx(0))),
		sf::Vertex(sf::Vector2f(1, fx(1)))
	};
}

float Line_yxmb::fx(float X)
{
	return (m*X) + b;
}

void Line_yxmb::bindToData(std::vector<dataPoint>& PointsData)
{
	this->PointsData = &PointsData;
}

void Line_yxmb::bindToWindow(sf::RenderWindow& rw)
{
	this->rw = &rw;
}

void Line_yxmb::gradientDescent(float learning_rate)
{
	for each (dataPoint p in *PointsData)
	{
		float x = p.Point.getPosition().x / rw->getSize().x;
		float y = p.Point.getPosition().y / rw->getSize().y;
		
		float yHat = fx(x);
		float error = (y - yHat);

		m += error * x * learning_rate;
		b += error * learning_rate;
	}
}

sf::Vertex * Line_yxmb::getDrawableLine()
{
	float y = fx(1);
	linePts = new sf::Vertex[2]{
		sf::Vertex(sf::Vector2f(0, fx(0))),
		sf::Vertex(sf::Vector2f(1, fx(1)))
	};
	return linePts;
}

sf::Vertex * Line_yxmb::mapPointsToScreen(sf::Vertex * drawableLine) {
	sf::Vertex* mappedLine = new sf::Vertex[2];

	for (int i = 0; i < 2; i++) {
		mappedLine[i].position.x = linePts[i].position.x * rw->getSize().x;
		mappedLine[i].position.y = linePts[i].position.y * rw->getSize().y;
	}

	return mappedLine;
}

Line_yxmb::~Line_yxmb()
{
}


