#include "app.h"

App::App()
{
}

App::~App()
{
}

void App::onInit(int argc, char* argv[])
{
	// Create window
	mainWindow = std::make_shared<sf::RenderWindow>(
		sf::VideoMode(mainWindowWidth, mainWindowHeight),
		name
	);

	// Create models
	solver = std::make_unique<Solver>();
	
	// Displayed stuff
	simulation = std::make_unique<Simulation>();

}

int App::exec()
{
	// Set play mode
	play();

	// Launch loop
	coreLoop();

	// Exit stuff
	onExit();

	// Return status code
	return 0;
}

void App::onExit()
{
}

void App::play()
{
	playing = true;
}

void App::pause()
{
	playing = false;
}

void App::reset()
{
	playing = false;
}

void App::processUserInputsAndEvents()
{
	// Events
	sf::Event event;
	mainWindow->pollEvent(event);
	if (event.type == sf::Event::Closed)
		mainWindow->close();
	
	// Keyboard inputs

	// Mouse inputs

}

void App::coreLoop()
{
	// Obj for loop
	sf::Clock clock;
	sf::Time remainingTime = sf::Time::Zero;
	sf::Time dt_s = sf::seconds(1.f / fps);

	// Main loop
	while (mainWindow->isOpen())
	{
		// Reset clock
		remainingTime += clock.restart();
		
		// Process inputs and events
		processUserInputsAndEvents();

		// While time is remaining to update the models
		// update the models
		while (remainingTime > dt_s) // time per frame
		{
			remainingTime -= dt_s;
			update(dt_s.asSeconds());
		}

		// Update screen
		render();
	}
}

void App::update(float dt_s)
{
	// Update the models
	//solver->solve(dt_s);
}

void App::render()
{
	// Clear window
	mainWindow->clear();

	// Render stuff
	simulation->render(mainWindow);
	// brain->render();
	// stats->render();

	// Display window
	mainWindow->display();
}