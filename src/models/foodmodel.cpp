#include "foodmodel.hpp"

FoodModel::FoodModel()
	: Model()
{

}

FoodModel::FoodModel(const double& x, const double& y)
	: Model()
{
	position = Vector2(x, y);
}