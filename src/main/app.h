#pragma once

#include <iostream>

#include "SFML/Graphics.hpp"

#include "common.h"
#include "../models/solver.h"
#include "simulation.h"

class App
{

private:
	// Constants
	const double mainWindowWidth{ 500 };
	const double mainWindowHeight{ 500 };
	const std::string name{ "ASLS" };
	const int fps{ 60 };

	// Core loop variables
	bool playing{ false };

	// Models
	std::unique_ptr<Solver> solver{ nullptr };

	// Displayed stuff
	std::shared_ptr<sf::RenderWindow> mainWindow{ nullptr };
	std::unique_ptr<Simulation> simulation{ nullptr };
	/*
	Stats
	Brain
	*/
	// ??? Genome* genome{ nullptr }; Can't remember why I used that

public:
	App();
	~App();

public:
	void onInit(int argc, char* argv[]);
	int exec();

private:
	void coreLoop();
	void processUserInputsAndEvents();
	void play();
	void pause();
	void reset();
	void onExit();
	void update(float dt_s);
	void render();

};
