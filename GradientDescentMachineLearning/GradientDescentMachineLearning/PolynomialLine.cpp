#include "PolynomialLine.h"


PolynomialLine::PolynomialLine(int degree, int resolution)
{
	//init minimum degree = 1
	//if (degree < 1) {
	//	degree = 1;
	//}
	PolynDegree = degree;

	//init minimum num of b 
	b = new float[degree+1];
	for (int d = 0; d < degree + 1; d++) {
		b[d] = 0;
	}
	//init minimum resolution
	if (resolution < degree + 1) {
		resolution = degree + 1;
	}
	res = resolution;

	//init line resolution points
	linePts = new sf::Vertex[res];
	linePts[0] = sf::Vertex(sf::Vector2f(0.0f,fx(0.0f)));
	resSpace = 1.0f / res;
	for (int i = 0; i < res; i++) {
		linePts[i] = sf::Vertex(sf::Vector2f(resSpace*i, fx(resSpace*i)));
	}
	mappedLine = new sf::Vertex[res];
}

float PolynomialLine::fx(float X)
{
	float yfinal = 0;
	for (int n = 0; n < PolynDegree + 1; n++) {
		yfinal += (b[n] * pow(X, n));
	}
	return yfinal;
}

void PolynomialLine::bindToData(std::vector<dataPoint>& PointsData)
{
	this->PointsData = &PointsData;
}

void PolynomialLine::bindToWindow(sf::RenderWindow& rw)
{
	this->rw = &rw;
}

sf::Vertex * PolynomialLine::getDrawableLine()
{
	//delete[] linePts;
	//linePts = new sf::Vertex[res];
	linePts[0] = sf::Vertex(sf::Vector2f(0, fx(0)));
	for (int i = 0; i < res; i++) {
		linePts[i] = sf::Vertex(sf::Vector2f(resSpace*i, fx(resSpace*i)));
	}
	return linePts;
}

sf::Vertex * PolynomialLine::mapPointsToScreen(sf::Vertex * drawableLine) {
	
	for (int i = 0; i < res; i++) {
		mappedLine[i].position.x = linePts[i].position.x * rw->getSize().x;
		mappedLine[i].position.y = linePts[i].position.y * rw->getSize().y;
	}

	return mappedLine;
}

void PolynomialLine::gradientDescent(float learning_rate)
{
	for each (dataPoint p in *PointsData)
	{
		float x = p.Point.getPosition().x / rw->getSize().x;
		float y = p.Point.getPosition().y / rw->getSize().y;

		float yHat = fx(x);
		float error = (y - yHat);

		for (int i = 0; i < PolynDegree + 1; i++) {
			b[i] += ((error) * (pow(x,i)) * learning_rate)/ PointsData->size();
		}
	}
}

void PolynomialLine::ordinaryLeastSquares() {
	float xsum = 0;
	float ysum = 0;
	float xysum = 0;
	float xsqrsum = 0;

	float xmean = 0;
	float ymean = 0;
	int n = 0;

	for each (dataPoint p in *PointsData)
	{
		n++;
		float x = p.Point.getPosition().x / rw->getSize().x;
		float y = p.Point.getPosition().y / rw->getSize().y;
		
		xsum += x;
		xsqrsum += pow(x, 2);
		ysum += y;
		xysum += x*y;
	}
	xmean = xsum / n;
	ymean = ysum / n;

	float num = 0;
	float den = 0;
	num = (ysum)*(xsqrsum) - (xsum)*(xysum);
	den = n*(xsqrsum) - pow(xsum, 2);
	b[0] = ((num / den));
	num = n*(xysum)-(xsum)*(ysum);
	den = n*xsqrsum - pow(xsum, 2);
	b[1] = ((num / den));

	//for each (dataPoint p in *PointsData)
	//{
	//	float x = p.Point.getPosition().x / rw->getSize().x;
	//	float y = p.Point.getPosition().y / rw->getSize().y;
	//	float num = 0;
	//	float den = 0;
	//	for (int i = 0; i < PolynDegree + 1; i++) {
	//		/*num += (x - xmean)*(y - ymean);
	//		den += pow((x - xmean), 2);
	//		b[i] =  ((num/den) * (pow(x, i))) ;*/
	//		
	//	}
	//}
}

void PolynomialLine::LeastSquares() {
	float xsum = 0;
	float ysum = 0;
	float xysum = 0;
	float xsqrsum = 0;
	int n = 0;

	for each (dataPoint p in *PointsData)
	{
		n++;
		float x = p.Point.getPosition().x / rw->getSize().x;
		float y = p.Point.getPosition().y / rw->getSize().y;

		xsum += x;
		xsqrsum += pow(x, 2);
		ysum += y;
		xysum += x*y;
	}

	float num = 0;
	float den = 0;

	num = (ysum)*(xsqrsum)-(xsum)*(xysum);
	den = n*(xsqrsum)-pow(xsum, 2);
	b[0] = (num / den);

	num = n*(xysum)-(xsum)*(ysum);
	den = n*(xsqrsum) - pow(xsum, 2);
	b[1] = (num / den);
}

void PolynomialLine::reset() {
	for (int d = 0; d < PolynDegree + 1; d++) {
		b[d] = 0;
	}
}
PolynomialLine::~PolynomialLine()
{
	delete[] b;
	delete[] linePts;
	delete[] mappedLine;
}
