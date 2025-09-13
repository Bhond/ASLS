#pragma once

#include <iostream>
#include <functional>

#include "genome.hpp"
#include "model.hpp"
#include "main/mymath.hpp"
#include "main/misc.hpp"

class EntityModel : public Model
{
public:
	Genome* genome{ nullptr };
	// double health{ 1.0 };
	// double hunger{ 0.0 };
	// double horniness{ 0.0 };
	// double eyeSightRadius{ 20.0 };
	// double eyeSightAngle{ 20.0 };
	Vector2 direction{ 1.0 , 0.0 };
	double size{ 20.0 };
	double r{ 1.0 };
	double g{ 1.0 };
	double b{ 1.0 };

private:
	// std::default_random_engine* generator{ nullptr };
	// double healthdecay{ 0.0 };
	// double metabolismCost{ 0.1 };
	// double hungerThreshold{ 0.8 };
	// double horninessdecay{ 0.1 };
	// double speed{ 50.0 };
	// std::function<Vector2(Vector2&, Vector2&, double&, double&)> foodFinder;

public:
	EntityModel(Vector2 startingPos);
	EntityModel(const EntityModel& other) = default; // For siblings
	~EntityModel();

public:
	void initGenome();
	void update(double dt);
	void performAction(double dt);
	void updateStats(double dt);
	void updateInputs();
	// void setFoodFinder(std::function<Vector2(Vector2&, Vector2&, double&, double&)> func);
};