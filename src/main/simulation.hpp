// #pragma once

// #include <iostream>
// #include <string>
// #include <vector>
// #include <cmath>
// #include <random>

// #include "SFML/Graphics.hpp"

// // #include "main/misc.h"
// // #include "graphics/entities.h"
// // #include "graphics/foods.h"

// class Simulation
// {

// private:
// 	// Graphics
// 	const sf::Color backgroundColor = sf::Color(5, 5, 10, 255);
// 	sf::RectangleShape background;

// 	// Controls
// 	// std::shared_ptr<Entities> entitiesGroupControl{ nullptr };
// 	// std::shared_ptr<Foods> foodsGroupControl{ nullptr };
// 	// std::shared_ptr<EntityModel> selectedModel{ nullptr };

// 	// Callbacks
// 	// std::function<void(EntityModel*)> onEntityModelSelected;
// 	// std::function<void(EntityModel*)> onEntityModelDeselected;

// public:
// 	Simulation();
// 	~Simulation();

// public:
// 	void render(std::shared_ptr<sf::RenderWindow> window);
// 	void mousePressEvent(const float& mousePosX, const float& mousePosY);

// private:
// 	void onInit();

// // public:
// // 	void setOnEntityModelSelected(std::function<void(EntityModel*)> func);
// // 	void setOnEntityModelDeselected(std::function<void(EntityModel*)> func);

// };

#pragma once

#include <optional> // for std::optional
#include <SFML/Graphics.hpp>
// #include <TGUI/TGUI.hpp>
// #include <TGUI/Backend/SFML-Graphics.hpp>
#include <iostream>
#include <chrono>
#include <ctime>

#include "main/misc.hpp"
#include "graphics/controls/entities.hpp"
#include "models/solver.hpp"
#include "graphics/ui/brain.hpp"

class Simulation
{
private:
    const double dt_s = 0.01;

    // Init states
    bool isDragging{false};
    bool isPlaying{false};

    sf::RenderWindow window;
    // std::unique_ptr<tgui::Gui> gui;
    sf::Clock clock;
    // tgui::ComboBox::Ptr     combo;
    // tgui::Button::Ptr       loadBtn;
    // tgui::ListBox::Ptr      list;

    // Models
	std::unique_ptr<Solver> solver{ nullptr };
    Brain* brain{ nullptr };

	// Controls
	std::unique_ptr<Entities> entitiesGroupControl{ nullptr };

public:
    Simulation() = default;
    ~Simulation() = default;

public:
    void init();
    void run();

private:
    // void createGUI();
    void handleInputs();
    void update();
    void render();
    void play();
    void pause();

private:
    double nowEpoch_s();
};