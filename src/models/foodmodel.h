#pragma once

#include "model.h"

class FoodModel : public Model
{
public:
	double radius{10.0};

public:
	FoodModel();
	FoodModel(const double& x, const double& y);
};