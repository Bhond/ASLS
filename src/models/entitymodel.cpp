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
    Genome::Node* node = genome->root;
    while (node)
    {
        if (node->name == outTurnAngle)
        {
            //direction = Vector2::rotate(direction, node->activation).unit();
        }
        else if (node->name == outPositionIncrement)
        {
            //position += direction * node->activation * dt;
        }
        else if (node->name == outLayEgg)
        {
            if (horniness > 0.90)
            {
                horniness = 0.0;
            }
        }
        node = node->next;
    }
}

void EntityModel::updateStats(double dt)
{
    metabolismCost = speed / (2.0 * size);
    hunger += metabolismCost * dt;
    hunger = std::min(std::max(hunger, 0.0), 1.0);
    if (hunger >= hungerThreshold)
    {
        health -= healthdecay * dt;
        health = std::min(std::max(health, 0.0), 1.0);
    }
    
    horniness += horninessdecay * dt;
}


void EntityModel::updateInputs()
{
    // Find food
    Vector2 foodPosition = foodFinder(position, direction, eyeSightRadius, eyeSightAngle);

    Genome::Node* node = genome->root;
    while (node)
    {
        if (node->name == inHealth)
        {
            node->state = health;
        }
        else if (node->name == inHunger)
        {
            node->state = hunger;
        }
        else if (node->name == inFoodPositionX)
        {
            node->state = foodPosition.x;
        }
        else if (node->name == inFoodPositionY)
        {
            node->state = foodPosition.y;
        }
        else if (node->name == inHorniness)
        {
            node->state = horniness;
        }
        else if (node->name == inSize)
        {
            node->state = size;
        }
        else if (node->name == inSpeed)
        {
            node->state = speed;
        }
        else if (node->name == inEyeSightRadius)
        {
            node->state = eyeSightRadius;
        }
        else if (node->name == inEyeSightAngle)
        {
            node->state = eyeSightAngle;
        }
        else if (node->name == inColorR)
        {
            node->state = 0;
        }
        else if (node->name == inColorG)
        {
            node->state = 0;
        }
        else if (node->name == inColorB)
        {
            node->state = 0;
        }
        node = node->next;
    }
}

void EntityModel::setFoodFinder(std::function<Vector2(Vector2&, Vector2&, double&, double&)> func)
{
    foodFinder = func;
}
