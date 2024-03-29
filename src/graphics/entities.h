#pragma once

#include "entity.h"
#include "groupcontrol.h"
#include "../models/entitymodel.h"

class Entities : public GroupControl<EntityModel>
{
public:
	Entities(sf::RenderWindow* w);
	~Entities();

public:
	void buildControl(EntityModel* model) override;
};