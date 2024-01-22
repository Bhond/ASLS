#pragma once

#include "food.h"
#include "groupcontrol.h"
#include "../models/foodmodel.h"

class Foods : public GroupControl<FoodModel>
{
public:
	Foods(sf::RenderWindow* w);
	~Foods();

public:
	void buildControl(FoodModel* model) override;
};