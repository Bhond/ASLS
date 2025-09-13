#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <random>
#include "../main/mymath.hpp"
#include "entitymodel.hpp"
// #include "foodmodel.h"

class Solver
{
public:
	std::vector<EntityModel*> entities;
private:
	// std::default_random_engine* generator;
	// std::function<void(EntityModel*)> func;
	// std::vector<FoodModel*> foods;
	std::function<void(EntityModel*)> onEntityModelCreated;
	std::function<void(EntityModel*)> onEntityModelDeleted;
	// std::function<void(FoodModel*)> onFoodModelCreated;
	// std::function<void(FoodModel*)> onFoodModelDeleted;

public:
	Solver();
	~Solver();

public:
	void solve(const double& dt_s);
	void addEntity();
	// void addFood();
	// void addFood(const double& x, const double& y);
	// Vector2 foodFinder(Vector2& position, Vector2& direction, double& radius, double& angle);

public:
	void setOnEntityModelCreated(std::function<void(EntityModel*)> func);
	void setOnEntityModelDeleted(std::function<void(EntityModel*)> func);
	// void setOnFoodModelCreated(std::function<void(FoodModel*)> func);
	// void setOnFoodModelDeleted(std::function<void(FoodModel*)> func);
};