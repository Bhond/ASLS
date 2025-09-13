#pragma once

#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "control.hpp"
#include "../models/entitymodel.hpp"

class Entity : public Control<EntityModel>
{
private:
	sf::ConvexShape* shape{ nullptr };
	sf::ConvexShape* eyeSightRegion{ nullptr };

public:
	Entity() = delete;
	Entity(EntityModel* m);
	~Entity();

public:
	void buildGeometry() override;
	void updateGeometryPosition(sf::RenderWindow& w) override;
	void draw(sf::RenderWindow& w) override;
	void onSelected(sf::RenderWindow& w) override;

};