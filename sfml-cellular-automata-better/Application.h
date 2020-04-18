#pragma once

#include <SFML/Graphics.hpp>

#include "SimulationGrid.h"

class Application
{
public:
	Application();
	void run();
private:
	void step();
	void render();
	//int findMaxValue();
private:
	sf::RenderWindow window_;
	SimulationGrid grid_;
	sf::Font font;
};

