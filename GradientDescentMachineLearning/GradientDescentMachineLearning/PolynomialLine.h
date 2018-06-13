#pragma once
#include <SFML\Graphics.hpp>

#include "dataPoint.h"

class PolynomialLine
{
public:
	PolynomialLine(int degree = 1, int resolution = 2);
	float fx(float X);
	void bindToData(std::vector<dataPoint>& PointsData);
	void bindToWindow(sf::RenderWindow & rw);
	sf::Vertex * getDrawableLine();
	sf::Vertex * mapPointsToScreen(sf::Vertex * drawableLine);
	void gradientDescent(float learning_rate);
	void ordinaryLeastSquares();
	void LeastSquares();
	void reset();
	~PolynomialLine();

	float* b;
	int PolynDegree;
	int res;
	float resSpace;
	std::vector<dataPoint>* PointsData;
	sf::Vertex* linePts;
	sf::Vertex* mappedLine;
	sf::RenderWindow* rw;
};

