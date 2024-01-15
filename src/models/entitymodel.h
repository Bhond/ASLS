#pragma once

#include "genome.h"

class EntityModel
{
private:
	double health{ 1.0 };
	double size{ 10.0 };
	double hunger{ 1.0 };
	Genome genome;

public:
	EntityModel();
	EntityModel(const EntityModel& other) = default; // For siblings

public:
	void initGenome();
	void update(double dt);
};