#pragma once

#include <iostream>
#include "control.h"
#include "../models/entitymodel.h"

class Entity : public Control<EntityModel>
{
private:

public:
	Entity() = delete;
	Entity(EntityModel* m);
	~Entity();

public:
	void draw() override;

};