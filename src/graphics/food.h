#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "control.h"
#include "../models/foodmodel.h"

class Food : public Control<FoodModel>
{
private:
	sf::CircleShape* shape{ nullptr };

public:
	Food() = delete;
	Food(FoodModel* m);
	~Food();

public:
	void buildGeometry() override;
	void updateGeometryPosition(sf::RenderWindow* w) override;
	void draw(sf::RenderWindow* w) override;
	void onSelected(sf::RenderWindow* w) override;

};