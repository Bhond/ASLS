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
    entitiesGroupControl->computeHitBoxes(this);
    selectedModel = entitiesGroupControl->hasHitAControl(event->localPos().x(), event->localPos().y());
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

    if (selectedModel)
    {
        Genome::Node* tmp = selectedModel->genome->root;
        double x = 50;
        double yStart = 100;
        double y = 100;
        double xStep = 100;
        double yStep = 100;
        while (tmp)
        {
            sf::CircleShape c { 20 };
            c.move(x, y);

            int idx0{ 0 };
            int idx1{ 0 };
            if (tmp->activation < 0)
            {
                idx1 = 4;
            }
            else
            {
                idx0 = 6;
                idx1 = 9;
            }

            double coef0 = std::abs(std::abs(tmp->activation) - 2.0) / 2.0;
            Color color0 = colorLerp(Colors[idx0], Colors[idx1], coef0);
            c.setFillColor(sf::Color(color0.r, color0.g, color0.b));
            draw(c);

            tmp->pos2DX = x + 20;
            tmp->pos2DY = y + 20;

            for (Genome::Connection* connection : tmp->incomingConnections)
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(connection->from->pos2DX, connection->from->pos2DY)),
                    sf::Vertex(sf::Vector2f(connection->to->pos2DX, connection->to->pos2DY))
                };
                if (connection->weight < 0)
                {
                    idx0 = 0;
                    idx1 = 4;
                }
                else
                {
                    idx0 = 6;
                    idx1 = 9;
                }
                double coef1 = std::abs(std::abs(connection->weight) - 2.0) / 2.0;
                Color color1 = colorLerp(Colors[idx0], Colors[idx1], coef0);
                line->color = sf::Color(color1.r, color1.g, color1.b);
                draw(line, 2, sf::Lines);
            }

            y += yStep;
            if ((tmp->next && tmp->next->type != tmp->type) || y > 500)
            {
                x += xStep;
                y = yStart;
            }
            tmp = tmp->next;
        }
    }    
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