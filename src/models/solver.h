#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../main/mymath.h"
#include "entitymodel.h"

class Solver
{
private:
	std::default_random_engine* generator;
	std::function<void(EntityModel*)> func;
	std::vector<EntityModel*> entities;
	std::function<void(EntityModel*)> onEntityModelCreated;
	std::function<void(EntityModel*)> onEntityModelDeleted;

public:
	Solver(sf::RenderWindow* w);
	~Solver();

public:
	void addEntity();
	void solve(double dt);

public:
	void setOnEntityModelCreated(std::function<void(EntityModel*)> func);
	void setOnEntityModelDeleted(std::function<void(EntityModel*)> func);
};