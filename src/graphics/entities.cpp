#include "entities.h"

Entities::Entities()
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

