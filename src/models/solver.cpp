#include "solver.h"

Solver::Solver(sf::RenderWindow* w)
{
    generator = new std::default_random_engine();
}

Solver::~Solver()
{
    delete generator;
}


void Solver::solve(double dt)
{
    // Add entity
    std::uniform_int_distribution<int> d(0, 200);
    if (d(*generator) == 0 && entities.size() < 2)
    {
        addEntity();
    }

    // Update
    std::vector<EntityModel*> deadEntities;
    for (EntityModel* m : entities)
    {
        m->update(dt);

        if (m->health == 0.0)
        {
            deadEntities.push_back(m);
        }
    }

    for (EntityModel* m : deadEntities)
    {
        entities.erase(std::remove(entities.begin(), entities.end(), m), entities.end());
        onEntityModelDeleted(m);
        delete m;
    }
    deadEntities.clear();
}

void Solver::addEntity()
{
    std::uniform_int_distribution<int> d(-200, 200);
    EntityModel* m = new EntityModel(Vector2(d(*generator), d(*generator)));
    m->initGenome();
    onEntityModelCreated(m);
    entities.push_back(m);
}

void Solver::setOnEntityModelCreated(std::function<void(EntityModel*)> func)
{
    onEntityModelCreated = func;
}

void Solver::setOnEntityModelDeleted(std::function<void(EntityModel*)> func)
{
    onEntityModelDeleted = func;
}