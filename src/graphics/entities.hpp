#pragma once

#include "entity.hpp"
#include "groupcontrol.hpp"
#include "../models/entitymodel.hpp"

class Entities : public GroupControl<EntityModel>
{
public:
	Entities();
	~Entities();

public:
	void buildControl(EntityModel* model) override;
};