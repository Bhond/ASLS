#pragma once

#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "control.h"
#include "../models/entitymodel.h"

class Entity : public Control<EntityModel>
{
private:
	sf::ConvexShape* shape{ nullptr };
	sf::ConvexShape* eyeSightRegion{ nullptr };

public:
	Entity() = delete;
	Entity(std::shared_ptr<EntityModel> m);
	~Entity();

public:
	void buildGeometry() override;
	void updateGeometryPosition(std::shared_ptr<sf::RenderWindow> w) override;
	void draw(std::shared_ptr<sf::RenderWindow> w) override;
	void onSelected(std::shared_ptr<sf::RenderWindow> w) override;

};