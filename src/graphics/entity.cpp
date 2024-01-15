#include "entity.h"

Entity::Entity(EntityModel* m)
	: Control(m)
{

}

Entity::~Entity()
{
	Entity::~Entity();
}

void Entity::draw()
{
	std::cout << "Entity drawn" << std::endl;
}
