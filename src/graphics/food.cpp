#include "food.h"

Food::Food(FoodModel* m)
	: Control(m)
{
}

Food::~Food()
{
	Food::~Food();
	delete shape;
}

void Food::buildGeometry()
{
	shape = new sf::CircleShape(model->radius);
	shape->setFillColor(sf::Color::Green);
	shapes.push_back(shape);
}

void Food::updateGeometryPosition(sf::RenderWindow* w)
{
	sf::Vector2f position = toVector2f(model->position);
	position += sf::Vector2f(w->getView().getSize().x / 2.0, w->getView().getSize().y / 2.0);

	// Main shape
	shape->setPosition(position);
}

void Food::draw(sf::RenderWindow* w)
{
	w->draw(*shape);
}

void Food::onSelected(sf::RenderWindow* w)
{
	if (selected)
	{
		shape->setOutlineColor(sf::Color::Red);
		shape->setOutlineThickness(2.0f);
	}
	else
	{
		shape->setOutlineColor(sf::Color::Transparent);
		shape->setOutlineThickness(0);
	}
}