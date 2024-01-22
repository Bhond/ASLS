#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

#include "SFML/Graphics.hpp"
#include <qevent.h>

#include "../main/misc.h"
#include "../graphics/qsfmlcanvas.h"
#include "../models/solver.h"
#include "../models/genome.h"
#include "../graphics/entities.h"
#include "../graphics/foods.h"

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
	Genome* genome{ nullptr };
	Entities* entitiesGroupControl{ nullptr };
	Foods* foodsGroupControl{ nullptr };
	EntityModel* selectedModel{ nullptr };

private:
	const sf::Color BackgroundColor = sf::Color(5, 5, 10, 255);
	sf::RectangleShape Background;
	std::function<void(EntityModel*)> onEntityModelSelected;
	std::function<void(EntityModel*)> onEntityModelDeselected;
	std::function<void(EntityModel*)> onSimulationRenderTick;

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
	void setOnEntityModelSelected(std::function<void(EntityModel*)> func);
	void setOnEntityModelDeselected(std::function<void(EntityModel*)> func);
	void setOnSimulationRenderTick(std::function<void(EntityModel*)> func);

protected:
	void onUpdate() override;

private:
	void onScroll(const double& amt) override;
	void mousePressEvent(QMouseEvent* event) override;

public slots:
	void render();
};