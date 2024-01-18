#include "entitymodel.h"

EntityModel::EntityModel(Vector2 startingPos)
{
    position = startingPos;
}

EntityModel::~EntityModel()
{
    delete generator;
	delete genome;
    generator = nullptr;
    genome = nullptr;
}

void EntityModel::initGenome()
{
	genome = new Genome();
    genome->addNode("Test0", Genome::NodeTypes::Input, Genome::SquashTypes::Identity);
    genome->addNode("Test1", Genome::NodeTypes::Input, Genome::SquashTypes::Identity);
    genome->addNode("Test2", Genome::NodeTypes::Input, Genome::SquashTypes::Identity);
    genome->addNode("Test3", Genome::NodeTypes::Hidden, Genome::SquashTypes::Identity);
    genome->addNode("Test7", Genome::NodeTypes::Hidden, Genome::SquashTypes::Identity);
    genome->addNode("Test4", Genome::NodeTypes::Output, Genome::SquashTypes::Identity);
    genome->addNode("Test5", Genome::NodeTypes::Output, Genome::SquashTypes::Identity);
    genome->addNode("Test6", Genome::NodeTypes::Output, Genome::SquashTypes::Identity);
}

void EntityModel::update(double dt)
{
    // Update inputs
    updateInputs();

    // Update genome
	genome->update();

    // Do action
    performAction(dt);

    // Update stats
    updateStats(dt);
}

void EntityModel::performAction(double dt)
{


}

void EntityModel::updateStats(double dt)
{
    hunger += hungerdecay * dt;
    hunger = std::min(std::max(hunger, 0.0), 1.0);
    if (hunger >= hungerThreshold)
    {
        health -= healthdecay * dt;
        health = std::min(std::max(health, 0.0), 1.0);
    }
}


void EntityModel::updateInputs()
{
}