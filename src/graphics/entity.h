#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "control.h"
#include "../models/entitymodel.h"

class Entity : public Control<EntityModel>
{
private:
	sf::ConvexShape* shape{ nullptr };
	sf::CircleShape* foodSearchRegion{ nullptr };

public:
	Entity() = delete;
	Entity(EntityModel* m);
	~Entity();

public:
	void buildGeometry() override;
	void updateGeometryPosition(sf::RenderWindow* w) override;
	void draw(sf::RenderWindow* w) override;
	void onSelected(sf::RenderWindow* w) override;

};