#include "entity.hpp"

Entity::Entity(EntityModel* m)
	: Control(m)
{
}

Entity::~Entity()
{
	Control::~Control();
	delete shape;
}

void Entity::buildGeometry()
{
	shape = new sf::ConvexShape(3);

	eyeSightRegion = new sf::ConvexShape(3);
	eyeSightRegion->setFillColor(sf::Color::Green);

	shapes.push_back(shape);
}

void Entity::updateGeometryPosition(sf::RenderWindow& w)
{
	// Color may change
	shape->setFillColor(sf::Color(pModel->r * 255, pModel->g * 255, pModel->b * 255, 255));

	sf::Vector2f position = toVector2f(pModel->position);
	position += sf::Vector2f(w.getView().getSize().x / 2.0, w.getView().getSize().y / 2.0);

	sf::Vector2f tangent = toVector2f(pModel->direction);
	Vector2 n = Vector2::rotate(pModel->direction, PI / 2.0);
	sf::Vector2f normal = sf::Vector2f((float)n.x, (float)n.y);

	// Main shape
	sf::Vector2f p0 = position + tangent * (float)pModel->size/2.0f;
	sf::Vector2f p2 = position - tangent * (float)pModel->size/2.0f + normal *  (float)pModel->size/2.0f;
	sf::Vector2f p1 = position - tangent * (float)pModel->size/2.0f - normal *  (float)pModel->size/2.0f;

	shape->setPoint(0, p0);
	shape->setPoint(1, p1);
	shape->setPoint(2, p2);
	
	// Eyesight
	// double length = pModel->eyeSightRadius * cos(pModel->eyeSightAngle / 2.0);
	// sf::Vector2f p3 = position;
	// sf::Vector2f p4 = position + tangent * (float)pModel->eyeSightRadius + normal *  (float)length/2.0f;
	// sf::Vector2f p5 = position + tangent * (float)pModel->eyeSightRadius - normal *  (float)length/2.0f;

	// eyeSightRegion->setPoint(0, p3);
	// eyeSightRegion->setPoint(1, p4);
	// eyeSightRegion->setPoint(2, p5);
}

void Entity::draw(sf::RenderWindow& w)
{
	w.draw(*shape);
}

void Entity::onSelected(sf::RenderWindow& w)
{
	if (selected)
	{
		w.draw(*eyeSightRegion);
		shape->setOutlineColor(sf::Color::Red);
		shape->setOutlineThickness(2.0f);
	}
	else
	{
		shape->setOutlineColor(sf::Color::Transparent);
		shape->setOutlineThickness(0);
	}
}