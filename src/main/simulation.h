#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

#include "SFML/Graphics.hpp"

#include "../main/misc.h"
#include "../graphics/entities.h"
#include "../graphics/foods.h"

class Simulation
{

private:
	// Graphics
	const sf::Color backgroundColor = sf::Color(5, 5, 10, 255);
	sf::RectangleShape background;

	// Controls
	std::shared_ptr<Entities> entitiesGroupControl{ nullptr };
	std::shared_ptr<Foods> foodsGroupControl{ nullptr };
	std::shared_ptr<EntityModel> selectedModel{ nullptr };

	// Callbacks
	std::function<void(EntityModel*)> onEntityModelSelected;
	std::function<void(EntityModel*)> onEntityModelDeselected;

public:
	Simulation();
	~Simulation();

public:
	void render(std::shared_ptr<sf::RenderWindow> window);
	void mousePressEvent(const float& mousePosX, const float& mousePosY);

private:
	void onInit();

public:
	void setOnEntityModelSelected(std::function<void(EntityModel*)> func);
	void setOnEntityModelDeselected(std::function<void(EntityModel*)> func);

};