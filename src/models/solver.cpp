#include "solver.h"

Solver::Solver(sf::RenderWindow* w)
{
    // Init entities
    entityTest = new EntityModel();
    entityTest->initGenome();
}

Solver::~Solver()
{
    delete entityTest;
}

void Solver::onEntityCreated(std::function<void(EntityModel*)>& lambda)
{
    lambda(entityTest);
}

void Solver::solve()
{

}