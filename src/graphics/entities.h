#pragma once

#include "entity.h"
#include "groupcontrol.h"
#include "../models/entitymodel.h"

class Entities : public GroupControl<EntityModel, Entity>
{
public:
	Entities();
	~Entities();

public:
	void buildControl(EntityModel* model) override;
};