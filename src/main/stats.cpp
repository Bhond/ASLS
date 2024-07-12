#include "stats.h"

Stats::Stats()
{
}

Stats::~Stats()
{
}

void Stats::onInit()
{	
}

void Stats::addPopulationSizeUpdate(int v)
{
	populationSize.push_back(v);
}

void Stats::clearPopulationSize()
{
	populationSize.clear();
}
