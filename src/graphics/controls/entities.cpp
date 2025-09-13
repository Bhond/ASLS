#include "entities.hpp"

Entities::Entities()
	: GroupControl()
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

