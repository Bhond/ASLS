#include "brain.hpp"

/// @brief Dtor
Brain::~Brain()
{
    selectedGenome = nullptr; // Deleted elsewhere
}

/// @brief Draw the selected genome
/// @param window The window to draw the genome on
void Brain::drawGenome(sf::RenderWindow& window)
{
    if (selectedGenome)
    {
        Genome::Node* tmp = selectedGenome->root;
        double originX{window.getSize().x * 0.75};
        double marginX{10.0};
        double marginY{10.0};
        double availableWidth = window.getSize().x  * 0.25 - 2 * marginX;
        double availableHeight = window.getSize().y * 0.25 - 2 * marginY;
        double yStepInputs = selectedGenome->inputSize == 1 ? 0.0 : availableHeight / ((double)selectedGenome->inputSize - 1);
        double yStepOutputs = selectedGenome->outputSize == 1 ? 0.0 : availableHeight / ((double)selectedGenome->outputSize - 1);
        double xStep = availableWidth / ((double)selectedGenome->outputLayerDepth);
        int tmpOutputIdx = 0;

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
                // Average of the incoming nodes' Y
                double meanFromY{ 0 };
                for (Genome::Connection* c : tmp->incomingConnections)
                {   
                    meanFromY += c->from->pos2DY;
                }
                tmp->pos2DY = meanFromY / tmp->incomingConnections.size();   
            }
            
            // Set x position
            tmp->pos2DX = originX + marginX + tmp->depth * xStep;
            
            // Draw actual node and its incoming connections
            drawNode(window, tmp);
            drawConnections(window, tmp);

            // Increment
            tmp = tmp->next;
        }
    }
}

/// @brief Draw a node
/// @param window The window on which the neuron is drawn
/// @param tmp The node to draw
void Brain::drawNode(sf::RenderWindow& window, Genome::Node* tmp)
{
    // Create and move shape
    sf::CircleShape c { (float)nodeRadius };
    c.move(sf::Vector2f(tmp->pos2DX, tmp->pos2DY));
    // Set the color of the neuron
    double coef0 = std::abs(std::abs(tmp->activation) - 2.0) / 2.0;
    Color color0 = colorLerp(Colors[0], Colors[Colors.size() - 1], coef0);
    c.setFillColor(sf::Color(color0.r, color0.g, color0.b));
    // Draw the neuron
    window.draw(c);
}

/// @brief Draw connections between nodes
/// @param window The window on which the neuron is drawn
/// @param tmp The node ast the end position of the connection
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
