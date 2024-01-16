#include "entity.h"

Entity::Entity(EntityModel* m)
	: Control(m)
{
}

Entity::~Entity()
{
	Entity::~Entity();
	delete shape;
}

void Entity::buildGeometry()
{
	shape = new sf::ConvexShape(3);
	shape->setFillColor(sf::Color::Cyan);
}

void Entity::updateGeometryPosition(sf::RenderWindow* w)
{
	sf::Vector2f position = sf::Vector2f(500.0, 500.0);
	
	sf::Vector2f tangent = sf::Vector2f(1.0, 0.0);
	sf::Vector2f normal = sf::Vector2f(0.0, 1.0);

	sf::Vector2f p0 = position + tangent * 10.0f;
	sf::Vector2f p1 = position - tangent * 10.0f + normal * 10.0f;
	sf::Vector2f p2 = position - tangent * 10.0f - normal * 10.0f;

	shape->setPoint(0, p0);
	shape->setPoint(1, p1);
	shape->setPoint(2, p2);
}

void Entity::draw(sf::RenderWindow* w)
{
	w->draw(*shape);
}
