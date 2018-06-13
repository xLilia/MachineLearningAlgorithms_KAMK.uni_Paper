#include <SFML/Graphics.hpp>
#include <iostream>

#include "Line_yxmb.h"
#include "PolynomialLine.h"
#include "dataPoint.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 720), "Simple Linear Regression & Gradient Descent");
	std::vector<dataPoint> PointsData;

	PolynomialLine pline(1,1000);
	pline.bindToData(PointsData);
	pline.bindToWindow(window);

	//Line_yxmb line;
	//line.bindToData(PointsData);
	//line.bindToWindow(window);

	bool process = 1;
	float lr = 0.02f;
	float lrstep = 0.01f;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseWheelScrolled) {
				if (event.key.code == sf::Mouse::VerticalWheel) {
					lr += event.mouseWheelScroll.delta * lrstep;
					std::cout << "LearningRate = " << lr << std::endl;
				}
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left) {
				std::cout << "dot!" << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << std::endl;
				PointsData.push_back(dataPoint(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)));
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::C) {
					std::cout << "clear!" << std::endl;
					PointsData.clear();
				}
				if (event.key.code == sf::Keyboard::R) {
					std::cout << "resetLine!" << std::endl;
					pline.reset();
					
				}
				if (event.key.code == sf::Keyboard::Space) {
					process = !process;
					if (process) {
						std::cout << "play!" << std::endl;
					}
					else {
						std::cout << "pause!" << std::endl;
					}
				}
			}
		}

		window.clear();
		for each (dataPoint p in PointsData)
		{
			window.draw(p.Point);
		}
		window.draw(pline.mapPointsToScreen(pline.getDrawableLine()), pline.res, sf::LineStrip);
		//window.draw(line.mapPointsToScreen(line.getDrawableLine()),2, sf::LineStrip);
		window.display();
		
		if (PointsData.size() > 1 && process) {
			if (lr < 0) {
				lr = 0;
			}
			//pline.gradientDescent(lr);
			pline.LeastSquares();
		}
			
	}

	return 0;
}
