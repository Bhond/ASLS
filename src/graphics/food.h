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
	Food(std::shared_ptr<FoodModel> m);
	~Food();

public:
	void buildGeometry() override;
	void updateGeometryPosition(std::shared_ptr<sf::RenderWindow> w) override;
	void draw(std::shared_ptr<sf::RenderWindow> w) override;
	void onSelected(std::shared_ptr<sf::RenderWindow> w) override;

};