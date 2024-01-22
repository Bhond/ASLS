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

	eyeSightRegion = new sf::ConvexShape(3);
	eyeSightRegion->setFillColor(sf::Color::Green);

	shapes.push_back(shape);
}

void Entity::updateGeometryPosition(sf::RenderWindow* w)
{
	sf::Vector2f position = toVector2f(model->position);
	position += sf::Vector2f(w->getView().getSize().x / 2.0, w->getView().getSize().y / 2.0);

	sf::Vector2f tangent = toVector2f(model->direction);
	Vector2 n = Vector2::rotate(model->direction, std::_Pi / 2.0);
	sf::Vector2f normal = sf::Vector2f((float)n.x, (float)n.y);

	// Main shape
	sf::Vector2f p0 = position + tangent * (float)model->size/2.0f;
	sf::Vector2f p2 = position - tangent * (float)model->size/2.0f + normal *  (float)model->size/2.0f;
	sf::Vector2f p1 = position - tangent * (float)model->size/2.0f - normal *  (float)model->size/2.0f;

	shape->setPoint(0, p0);
	shape->setPoint(1, p1);
	shape->setPoint(2, p2);
	
	// Eyesight
	double length = model->eyeSightRadius * cos(model->eyeSightAngle / 2.0);
	sf::Vector2f p3 = position;
	sf::Vector2f p4 = position + tangent * (float)model->eyeSightRadius + normal *  (float)length/2.0f;
	sf::Vector2f p5 = position + tangent * (float)model->eyeSightRadius - normal *  (float)length/2.0f;

	eyeSightRegion->setPoint(0, p3);
	eyeSightRegion->setPoint(1, p4);
	eyeSightRegion->setPoint(2, p5);


}

void Entity::draw(sf::RenderWindow* w)
{
	w->draw(*shape);
}

void Entity::onSelected(sf::RenderWindow* w)
{
	if (selected)
	{
		w->draw(*eyeSightRegion);
		shape->setOutlineColor(sf::Color::Red);
		shape->setOutlineThickness(2.0f);
	}
	else
	{
		shape->setOutlineColor(sf::Color::Transparent);
		shape->setOutlineThickness(0);
	}
}