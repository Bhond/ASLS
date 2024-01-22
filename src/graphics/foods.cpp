#include "Foods.h"

Foods::Foods(sf::RenderWindow* w)
	: GroupControl(w)
{
}

Foods::~Foods()
{
	GroupControl::~GroupControl();
}

void Foods::buildControl(FoodModel* model)
{
	GroupControl::buildControl(new Food(model));
}

