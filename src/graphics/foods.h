#pragma once

#include "food.h"
#include "groupcontrol.h"
#include "../models/foodmodel.h"

class Foods : public GroupControl<FoodModel>
{
public:
	Foods();
	~Foods();

public:
	void buildControl(std::shared_ptr<FoodModel> model) override;
};