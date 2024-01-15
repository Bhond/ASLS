#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../main/mymath.h"
#include "entitymodel.h"

class Solver
{
private:
	EntityModel* entityTest{ nullptr };

public:
	Solver(sf::RenderWindow* w);
	~Solver();

public:
	void onEntityCreated(std::function<void(EntityModel*)>& lambda);
	void solve();
};