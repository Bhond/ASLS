#pragma once

#include <iostream>
#include <vector>
#include "../models/genome.h"

class Stats
{
private:
	std::vector<int> populationSize;

public:
	Stats();
	~Stats();

public:
	void onInit();

public:
	void addPopulationSizeUpdate(int v);
	void clearPopulationSize();

};