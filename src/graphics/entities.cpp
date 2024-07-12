#include "entities.h"

Entities::Entities()
	: GroupControl()
{
}

Entities::~Entities()
{
	GroupControl::~GroupControl();
}

void Entities::buildControl(std::shared_ptr<EntityModel> model)
{
	GroupControl::buildControl(std::make_shared<Entity>(model));
}

