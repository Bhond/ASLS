#pragma once

#include "entity.h"
#include "groupcontrol.h"
#include "../models/entitymodel.h"

class Entities : public GroupControl<EntityModel>
{
public:
	Entities();
	~Entities();

public:
	void buildControl(std::shared_ptr<EntityModel> model) override;
};