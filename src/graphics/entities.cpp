#include "entities.h"

Entities::Entities(sf::RenderWindow* w)
	: GroupControl(w)
{
}

Entities::~Entities()
{
	GroupControl::~GroupControl();
}

void Entities::buildControl(EntityModel* model)
{
	GroupControl::buildControl(new Entity(model));
}

