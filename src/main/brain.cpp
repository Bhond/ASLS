#include "brain.h"

Brain::Brain(QWidget* parent, unsigned int frameTime)
    : QSFMLCanvas(parent, frameTime)
{
}

Brain::Brain(QWidget* parent, const QPoint& position, const QSize& size, unsigned int frameTime)
    : QSFMLCanvas(parent, position, size, frameTime)
{
}

Brain::~Brain()
{
	selectedGenome; // Deleted elsewhere
}

void Brain::drawGenome()
{
    if (selectedGenome)
    {
        Genome::Node* tmp = selectedGenome->root;

        // First, find the number of hidden layers
        int nHiddenLayers = computeNHiddenLayers();

        double availableWidth = width() - 2 * marginX;
        double availableHeight = height() - 2 * marginY;

        double x = marginX;
        double xStep = availableWidth / (2.0 + nHiddenLayers);
        double yStepInputs = availableHeight / ((double)selectedGenome->inputSize);
        double y = (height() / 2.0) - (selectedGenome->inputSize / 2) * yStepInputs;
        double yStepOutputs = availableHeight / ((double)selectedGenome->outputSize);
        double yStep{ yStepInputs };
        while (tmp)
        {
            if (tmp->type == Genome::NodeTypes::Output)
            {
                yStep = yStepOutputs;
            }
            else if (tmp->type == Genome::NodeTypes::Hidden)
            {
                yStep = 5 * nodeRadius;
            }

            sf::CircleShape c { (float)nodeRadius };
            c.move(x, y);

            double coef0 = std::abs(std::abs(tmp->activation) - 2.0) / 2.0;
            Color color0 = colorLerp(Colors[0], Colors[Colors.size() - 1], coef0);
            c.setFillColor(sf::Color::Red); // (color0.r, color0.g, color0.b)
            draw(c);

            tmp->pos2DX = x + nodeRadius;
            tmp->pos2DY = y + nodeRadius;

            y += yStep;
            bool increment = false;
            if (tmp->next && tmp->next->type == Genome::NodeTypes::Hidden)
            {
                for (Genome::Connection* c : tmp->incomingConnections)
                {
                    if (c->from->type == Genome::NodeTypes::Hidden)
                    {
                        increment = true;
                        break;
                    }
                }
            }

            if (tmp->next && (tmp->next->type != tmp->type 
                 || increment))
            {
                x += xStep;
                if (tmp->next->type == Genome::NodeTypes::Output)
                {
                    y = (height() / 2.0) - (selectedGenome->outputSize / 2) * yStepOutputs;
                }
                else
                {
                    double cumulY{ 0.0 };
                    for (Genome::Connection* c : tmp->incomingConnections)
                    {
                        cumulY += c->from->pos2DY;
                    }
                    if (cumulY > 0.0)
                    {
                        y = marginY; //cumulY / ((double)tmp->incomingConnections.size());
                    }
                    else
                    {
                        y = marginY;
                    }
                }
            }

            for (Genome::Connection* connection : tmp->incomingConnections)
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(connection->from->pos2DX, connection->from->pos2DY)),
                    sf::Vertex(sf::Vector2f(connection->to->pos2DX, connection->to->pos2DY))
                };
                line->color = sf::Color::Green;
                draw(line, 2, sf::Lines);
            }

            tmp = tmp->next;
        }
    }
}

void Brain::onInit()
{
    // Background
    sf::Vector2<float> size(width(), height());
    Background = sf::RectangleShape(size);
    Background.setFillColor(BackgroundColor);
}

void Brain::reset()
{
}

void Brain::onUpdate()
{
    if (playing)
    {
    }
    render();
}

int Brain::computeNHiddenLayers()
{
    int result{ 0 };
    int nNode{ 0 };

    Genome::Node* tmp = selectedGenome->root;
    while (tmp->next && tmp->next->type != Genome::NodeTypes::Output)
    {
        if (tmp->type == Genome::NodeTypes::Hidden)
        {
            for (Genome::Connection* c : tmp->incomingConnections)
            {
                if (c->from->type == Genome::NodeTypes::Hidden)
                {
                    result++;
                    nNode = 0;
                    break;
                }
            }
        }
        nNode++;
        tmp = tmp->next;
    }
    return result;
}

void Brain::render()
{
    // Clear canvas
    clear();

    // Draw background
    draw(Background);
    drawGenome();
}

void Brain::setSelectedGenome(Genome* genome)
{
	selectedGenome = genome;
}
