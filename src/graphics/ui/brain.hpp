#pragma once

#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"
#include "main/misc.hpp"
#include "models/genome.hpp"

class Brain
{

private:
	const double nodeRadius{ 5.0 };
	Genome* selectedGenome{ nullptr };

public:
	Brain() = default;
	~Brain();

public:
	void drawGenome(sf::RenderWindow& window);
	void drawNode(sf::RenderWindow& window, Genome::Node* tmp);
	void updateCoordinates(double& x, double xStep, Genome::Node* tmp, double& y, double yStepOutputs, double yStepInputs);
	void drawConnections(sf::RenderWindow& window, Genome::Node* tmp);

public:
	void setSelectedGenome(Genome* genome);
};