#include "entitymodel.h"

EntityModel::EntityModel()
{
}

void EntityModel::initGenome()
{
	genome.addNode("Test0", Genome::NodeTypes::Input, Genome::SquashTypes::Identity);
	genome.addNode("Test1", Genome::NodeTypes::Output, Genome::SquashTypes::Identity);
	genome.addNode("Test2", Genome::NodeTypes::Hidden, Genome::SquashTypes::Identity);
	genome.addNode("Test3", Genome::NodeTypes::Output, Genome::SquashTypes::Identity);
	genome.addNode("Test4", Genome::NodeTypes::Input, Genome::SquashTypes::Identity);
	genome.addNode("Test5", Genome::NodeTypes::Hidden, Genome::SquashTypes::Identity);
	//0,4,2,5,1,3
}

void EntityModel::update(double dt)
{
	genome.update();
}