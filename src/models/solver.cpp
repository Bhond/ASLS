#include "solver.hpp"

Solver::Solver()
{
    // generator = new std::default_random_engine();
}

Solver::~Solver()
{
    // delete generator;

    for (EntityModel* e : entities)
    {
        delete e;
    }
    entities.clear();
    // for (FoodModel* f : foods)
    // {
    //     delete f;
    // }
    // foods.clear();

}


void Solver::solve(const double& dt_s)
{
    // Add entity
    // std::uniform_int_distribution<int> d(0, 200);
    // if (d(*generator) == 0 && entities.size() < 1)
    if (entities.size() < 1)
    {
        addEntity();
    }

    // Update
    std::vector<EntityModel*> deadEntities;
    for (EntityModel* m : entities)
    {
        m->update(dt_s);

        // if (m->health == 0.0)
        // {
        //     deadEntities.push_back(m);
        // }
    }

    // for (EntityModel* m : deadEntities)
    // {
    //     entities.erase(std::remove(entities.begin(), entities.end(), m), entities.end());
    //     onEntityModelDeleted(m);
    //     delete m;
    // }
    // deadEntities.clear();
}

void Solver::addEntity()
{
    // std::uniform_int_distribution<int> d(-200, 200);
    // EntityModel* m = new EntityModel(Vector2(d(*generator), d(*generator)));
    EntityModel* m = new EntityModel(Vector2(0.0, 0.0));
    // m->setFoodFinder([this](Vector2& p, Vector2& d, double& r, double& a) -> Vector2 {return foodFinder(p, d, r, a); });
    m->initGenome();
    onEntityModelCreated(m);
    entities.push_back(m);
}

// void Solver::addFood()
// {
//     FoodModel* m = new FoodModel();
//     onFoodModelCreated(m);
// }

// void Solver::addFood(const double& x, const double& y)
// {
//     FoodModel* m = new FoodModel(x, y);
//     m->position -= Vector2(m->radius, m->radius);
//     onFoodModelCreated(m);
//     foods.push_back(m);
// }

void Solver::setOnEntityModelCreated(std::function<void(EntityModel*)> func)
{
    onEntityModelCreated = func;
}

void Solver::setOnEntityModelDeleted(std::function<void(EntityModel*)> func)
{
    onEntityModelDeleted = func;
}

// Vector2 Solver::foodFinder(Vector2& position, Vector2& direction, double& radius, double& angle)
// {
//     Vector2 result{ -1.0, -1.0 };
//     for (FoodModel* food : foods)
//     {
//         Vector2 v = position - food->position;
//         double dx = v.length();

//         // If the food is close enougth
//         if (dx <= radius)
//         {
//             // Compute dot product
//             Vector2 v1 = v.unit();
//             double dot = Vector2::dot(v1, direction);
//             if (angle > acos(std::min(std::max(dot, 0.0), 1.0)))
//             {
//                 // Find first food close enougth
//                 result = food->position;
//                 break;
//             }
//         }
//     }
//     return result;
// }

// void Solver::setOnFoodModelCreated(std::function<void(FoodModel*)> func)
// {
//     onFoodModelCreated = func;
// }

// void Solver::setOnFoodModelDeleted(std::function<void(FoodModel*)> func)
// {
//     onFoodModelDeleted = func;
// }