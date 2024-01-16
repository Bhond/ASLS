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
    delete testModel;
    delete entitiesGroupControl;
}

void Simulation::onInit()
{
    sf::Vector2<float> size(width(), height());
    scaleWidth = simulatedWidth / width();
    scaleHeight = simulatedHeight / height();

    Background = sf::RectangleShape(size);
    Background.setFillColor(BackgroundColor);

    entitiesGroupControl = new Entities(this);
    testModel = new EntityModel();
    entitiesGroupControl->buildControl(testModel);

    solver = new Solver(this);
    //genome.addNode("Test0", Genome::NodeTypes::Input, Genome::SquashTypes::Identity);
    //genome.addNode("Test1", Genome::NodeTypes::Output, Genome::SquashTypes::Identity);
    //genome.addNode("Test2", Genome::NodeTypes::Hidden, Genome::SquashTypes::Identity);
    //genome.addNode("Test3", Genome::NodeTypes::Output, Genome::SquashTypes::Identity);
    //genome.addNode("Test4", Genome::NodeTypes::Input, Genome::SquashTypes::Identity);
    //genome.addNode("Test5", Genome::NodeTypes::Input, Genome::SquashTypes::Identity);
    //genome.addNode("Test6", Genome::NodeTypes::Input, Genome::SquashTypes::Identity);
    //genome.addNode("Test7", Genome::NodeTypes::Hidden, Genome::SquashTypes::Identity);
    //genome.addNode("Test8", Genome::NodeTypes::Output, Genome::SquashTypes::Identity);
    ////0,4,2,5,1,3

}

void Simulation::onScroll(const double& amt)
{
    if (amt < 0) // up Wheel
        zoomFactor += 1;
    else if (amt > 0 && zoomFactor > 1) //down Wheel
        zoomFactor -= 1;
}

void Simulation::onUpdate()
{
    if (playing)
    {
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

    /*Genome::Node* tmp = genome.root;
    double x = 50;
    double yStart = 100;
    double y = 100;
    double xStep = 100;
    double yStep = 100;
    while (tmp)
    {
        sf::CircleShape c { 20 };
        c.move(x, y);
        c.setFillColor(sf::Color::Red);
        draw(c);
        y += yStep;
        if (tmp->next && tmp->next->type != tmp->type)
        {
            x += xStep;
            y = yStart;
        }
        tmp = tmp->next;
    }*/

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