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

	foodSearchRegion = new sf::CircleShape(model->foodSearchRadius);
	foodSearchRegion->setFillColor(sf::Color::Green);

	shapes.push_back(shape);
	shapes.push_back(foodSearchRegion);
}

void Entity::updateGeometryPosition(sf::RenderWindow* w)
{
	sf::Vector2f position{ (float)model->position.x, (float)model->position.y };
	position += sf::Vector2f(w->getView().getSize().x / 2.0, w->getView().getSize().y / 2.0);

	sf::Vector2f tangent = sf::Vector2f(1.0, 0.0);
	sf::Vector2f normal = sf::Vector2f(0.0, 1.0);

	sf::Vector2f p0 = position + tangent * 40.0f;
	sf::Vector2f p1 = position + normal * 10.0f;
	sf::Vector2f p2 = position - normal * 10.0f;

	shape->setPoint(0, p0);
	shape->setPoint(1, p1);
	shape->setPoint(2, p2);

	foodSearchRegion->setPosition(position - sf::Vector2f(model->foodSearchRadius, model->foodSearchRadius));
}

void Entity::draw(sf::RenderWindow* w)
{
	w->draw(*shape);
}

void Entity::onSelected(sf::RenderWindow* w)
{
	if (selected)
	{
		shape->setOutlineColor(sf::Color::Red);
		shape->setOutlineThickness(2.0f);
		w->draw(*foodSearchRegion);
	}
	else
	{
		shape->setOutlineColor(sf::Color::Transparent);
		shape->setOutlineThickness(0);
	}
}