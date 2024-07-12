#include "Foods.h"

Foods::Foods()
	: GroupControl()
{
}

Foods::~Foods()
{
	GroupControl::~GroupControl();
}

void Foods::buildControl(std::shared_ptr<FoodModel> model)
{
	GroupControl::buildControl(std::make_shared<Food>(model));
}

