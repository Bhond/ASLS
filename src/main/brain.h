#pragma once

#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"

#include <qwidget.h>

#include "../graphics/qsfmlcanvas.h"
#include "../main/misc.h"
#include "../models/genome.h"

class Brain : public QSFMLCanvas
{

private:
	const double nodeRadius{ 10.0 };
	const double marginX{ 50.0 };
	const double marginY{ 50.0 };
	const sf::Color BackgroundColor = sf::Color(5, 5, 10, 255);
	sf::RectangleShape Background;
	Genome* selectedGenome{ nullptr };

public:
	Brain(QWidget* parent, unsigned int frameTime = 0);
	Brain(QWidget* parent, const QPoint& position, const QSize& size, unsigned int frameTime = 0);
	~Brain();

public:
	void drawGenome();
	void drawNode(double x, double y, Genome::Node* tmp);
	bool checkIncrement(Genome::Node* tmp);
	void updateCoordinates(double& x, double xStep, Genome::Node* tmp, double& y, double yStepOutputs, double yStepInputs);
	void drawConnections(Genome::Node* tmp);
	void onInit() override;
	void reset() override;

protected:
	void onUpdate() override;

private:
	int computeNHiddenLayers();

public:
	void setSelectedGenome(Genome* genome);

public slots:
	void render();
};