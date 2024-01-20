#pragma once

#include "genome.h"
#include "model.h"
#include "../main/mymath.h"

class EntityModel : public Model
{
public:
	Genome* genome{ nullptr };
	double health{ 1.0 };
	double hunger{ 0.0 };
	double foodSearchRadius{ 20.0 };

private:
	std::default_random_engine* generator{ nullptr };
	double healthdecay{ 0.0 };
	double hungerdecay{ 0.1 };
	double hungerThreshold{ 0.8 };
	double horniness{ 0.0 };
	double horninessdecay{ 0.1 };
	double size{ 10.0 };
	double speed{ 50.0 };
	Vector2 direction{ 1.0 , 0.0 };

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
};