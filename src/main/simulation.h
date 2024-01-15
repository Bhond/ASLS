#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

#include "SFML/Graphics.hpp"

#include "../graphics/qsfmlcanvas.h"
#include "../models/solver.h"

class Simulation : public QSFMLCanvas
{
	Q_OBJECT

public:
	Solver* solver = nullptr;

private:
	const double simulatedWidth  { 1e10 };
	const double simulatedHeight { 1e10 };
	const std::string Name { "ASLS" };
	double scaleWidth { 1 };
	double scaleHeight { 1 };
	double zoomFactor { 1 };

private:
	const sf::Color BackgroundColor = sf::Color(5, 5, 10, 255);
	sf::RectangleShape Background;

public:
	Simulation(QWidget* parent, unsigned int frameTime = 0);
	Simulation(QWidget* parent, const QPoint& position, const QSize& size, unsigned int frameTime = 0);
	~Simulation();
	
public:
	void onInit() override;
	void reset() override;
	double getScaleWidth();
	double getScaleHeight();
	void setScaleWidth(const double& amt);
	void setScaleHeight(const double& amt);

protected:
	void onUpdate() override;

private:
	void onScroll(const double& amt) override;

public slots:
	void render();
};