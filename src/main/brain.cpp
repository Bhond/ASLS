#include "brain.hpp"

Brain::Brain(unsigned int frameTime)
{
}

Brain::~Brain()
{
    selectedGenome = nullptr; // Deleted elsewhere
}

void Brain::drawGenome(sf::RenderWindow& window)
{
    if (selectedGenome)
    {
        Genome::Node* tmp = selectedGenome->root;
        double marginX = 50.0;
        double marginY = 50.0;
        double availableWidth = window.getSize().x - 2 * marginX;
        double availableHeight = window.getSize().y - 2 * marginY;
        double yStepInputs = availableHeight / ((double)selectedGenome->inputSize);
        double yStepOutputs = availableHeight / ((double)selectedGenome->outputSize);
        int tmpOutputIdx = 0;
        double xStep = availableWidth / ((double)selectedGenome->outputLayerDepth);

        // Compute 2d coordinates
        while (tmp)
        {
            if (tmp->type == Genome::NodeTypes::Input)
            {
                tmp->pos2DY = marginY + tmp->idx * yStepInputs;
            }
            else if (tmp->type == Genome::NodeTypes::Output)
            {
                tmp->pos2DY =  marginY + tmpOutputIdx * yStepOutputs;
                tmpOutputIdx += 1; // To Change for right idx
            }
            else // tmp->type == Genome::NodeTypes::Hidden
            {
                double meanFromY{ 0 };
                for (Genome::Connection* c : tmp->incomingConnections)
                {   
                    meanFromY += c->from->pos2DY;
                }

                tmp->pos2DY = meanFromY / tmp->incomingConnections.size();   
                    std::cout << "meanFromY:" << meanFromY << std::endl;
            }
            
            // Set x position
            tmp->pos2DX = marginX + tmp->depth * xStep;
            
            // Draw actual node and its incoming connections
            drawNode(window, tmp);
            drawConnections(window, tmp);

            // Increment
            tmp = tmp->next;
        }
    }
}

void Brain::drawNode(sf::RenderWindow& window, Genome::Node* tmp)
{
    sf::CircleShape c { (float)nodeRadius };
    c.move(sf::Vector2f(tmp->pos2DX, tmp->pos2DY));

    double coef0 = std::abs(std::abs(tmp->activation) - 2.0) / 2.0;
    Color color0 = colorLerp(Colors[0], Colors[Colors.size() - 1], coef0);
    
    if (tmp->type == Genome::NodeTypes::Input)
        c.setFillColor(sf::Color::Red);
    else if (tmp->type == Genome::NodeTypes::Output)
        c.setFillColor(sf::Color::Blue);
    else // tmp->type == Genome::NodeTypes::Hidden
        c.setFillColor(sf::Color::Green);

    // c.setFillColor(sf::Color(color0.r, color0.g, color0.b));
    window.draw(c);
}

void Brain::drawConnections(sf::RenderWindow& window, Genome::Node* tmp)
{
    for (Genome::Connection* connection : tmp->incomingConnections)
    {
        std::array line =
        {
            sf::Vertex{sf::Vector2f(connection->from->pos2DX + nodeRadius, connection->from->pos2DY + nodeRadius), sf::Color::Red},
            sf::Vertex{sf::Vector2f(connection->to->pos2DX + nodeRadius, connection->to->pos2DY + nodeRadius), sf::Color::Red}
        };
        double coef1 = std::abs(std::abs(connection->weight) - 2.0) / 2.0;
        Color color1 = colorLerp(Colors[0], Colors[Colors.size() - 1], coef1);
        window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
    }
}

void Brain::setSelectedGenome(Genome* genome)
{
	selectedGenome = genome;
}
