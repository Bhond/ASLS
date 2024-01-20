#include "simulation.h"

Simulation::Simulation(QWidget* parent, unsigned int frameTime)
    : QSFMLCanvas(parent, frameTime)
{
}

Simulation::Simulation(QWidget* parent, const QPoint& position, const QSize& size, unsigned int frameTime)
    : QSFMLCanvas(parent, position, size, frameTime)
{
}

Simulation::~Simulation()
{
    delete solver;
    delete entitiesGroupControl;
    delete genome;
    selectedModel = nullptr; // Destroyed elsewhere
}

void Simulation::onInit()
{
    sf::Vector2<float> size(width(), height());
    scaleWidth = simulatedWidth / width();
    scaleHeight = simulatedHeight / height();

    Background = sf::RectangleShape(size);
    Background.setFillColor(BackgroundColor);

    entitiesGroupControl = new Entities(this);

    solver = new Solver(this);
    solver->setOnEntityModelCreated([this](EntityModel* m) {
        if (m)
        {
            entitiesGroupControl->buildControl(m);
        }
        });
    solver->setOnEntityModelDeleted([this](EntityModel* m) {
        if (m == selectedModel)
        {
            onEntityModelDeselected(selectedModel);
            selectedModel = nullptr;
        }
        });
}

void Simulation::onScroll(const double& amt)
{
    if (amt < 0) // up Wheel
        zoomFactor += 1;
    else if (amt > 0 && zoomFactor > 1) //down Wheel
        zoomFactor -= 1;
}

void Simulation::mousePressEvent(QMouseEvent* event)
{
    // Retrieve the hitboxes
    entitiesGroupControl->computeHitBoxes(this);

    // Deselct model if one is already selected
    if (selectedModel)
    {
        onEntityModelDeselected(selectedModel);
    }

    // Retrieve the new selected model
    selectedModel = entitiesGroupControl->hasHitAControl(event->localPos().x(), event->localPos().y());

    // Do stuff
    if (selectedModel)
        onEntityModelSelected(selectedModel);
    else
        onEntityModelDeselected(selectedModel);

}

void Simulation::onUpdate()
{
    if (playing)
    {
        solver->solve(((double)myTimer.interval()) / 1000);
    }
    render();
}

void Simulation::reset()
{
    pause();
}

void Simulation::render()
{
    // Clear canvas
    clear();

    // Draw background
    draw(Background);

    // Draw controls
    entitiesGroupControl->draw();
    onSimulationRenderTick(selectedModel);
}

double Simulation::getScaleWidth()
{
    return scaleWidth;
}

double Simulation::getScaleHeight()
{
    return scaleHeight;
}

void Simulation::setScaleWidth(const double& amt)
{
    scaleWidth = amt;
}

void Simulation::setScaleHeight(const double& amt)
{
    scaleHeight = amt;
}

void Simulation::setOnEntityModelSelected(std::function<void(EntityModel*)> func)
{
    onEntityModelSelected = func;
}

void Simulation::setOnEntityModelDeselected(std::function<void(EntityModel*)> func)
{
    onEntityModelDeselected = func;
}

void Simulation::setOnSimulationRenderTick(std::function<void(EntityModel*)> func)
{
    onSimulationRenderTick = func;
}