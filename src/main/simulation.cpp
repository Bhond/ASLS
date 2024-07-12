#include "simulation.h"

Simulation::Simulation()
{
    // Initialize the simulation
    onInit();
}

Simulation::~Simulation()
{
}

void Simulation::onInit()
{
    background = sf::RectangleShape(sf::Vector2f(250.0f, 250.0f));
    background.setFillColor(sf::Color::Red);
}

void Simulation::mousePressEvent(const float& mousePosX, const float& mousePosY)
{
    //// Retrieve the hitboxes
    ////entitiesGroupControl->computeHitBoxes();

    //// Deselct model if one is already selected
    //if (selectedModel)
    //{
    //    onEntityModelDeselected(selectedModel);
    //}

    //// Retrieve the new selected model
    ////selectedModel = entitiesGroupControl->hasHitAControl(event->localPos().x(), event->localPos().y());

    //// Do stuff
    //if (selectedModel)
    //{
    //    onEntityModelSelected(selectedModel);
    //}
    //else
    //{
    //    onEntityModelDeselected(selectedModel);
    //    solver->addFood(event->localPos().x() - width()/2.0, event->localPos().y() - height()/2.0);
    //}
}

void Simulation::render(std::shared_ptr<sf::RenderWindow> window)
{
    // Draw background
    window->draw(background);

    //// Draw controls
    //entitiesGroupControl->draw();
    //foodsGroupControl->draw();
    //onSimulationRenderTick(selectedModel);
}

void Simulation::setOnEntityModelSelected(std::function<void(EntityModel*)> func)
{
    onEntityModelSelected = func;
}

void Simulation::setOnEntityModelDeselected(std::function<void(EntityModel*)> func)
{
    onEntityModelDeselected = func;
}