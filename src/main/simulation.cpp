// #include "simulation.h"

// Simulation::Simulation()
// {
//     // Initialize the simulation
//     onInit();
// }


// void Simulation::onInit()
// {
//     background = sf::RectangleShape(sf::Vector2f(250.0f, 250.0f));
//     background.setFillColor(sf::Color::Red);
// }

// void Simulation::mousePressEvent(const float& mousePosX, const float& mousePosY)
// {
//     //// Retrieve the hitboxes
//     ////entitiesGroupControl->computeHitBoxes();

//     //// Deselct model if one is already selected
//     //if (selectedModel)
//     //{
//     //    onEntityModelDeselected(selectedModel);
//     //}

//     //// Retrieve the new selected model
//     ////selectedModel = entitiesGroupControl->hasHitAControl(event->localPos().x(), event->localPos().y());

//     //// Do stuff
//     //if (selectedModel)
//     //{
//     //    onEntityModelSelected(selectedModel);
//     //}
//     //else
//     //{
//     //    onEntityModelDeselected(selectedModel);
//     //    solver->addFood(event->localPos().x() - width()/2.0, event->localPos().y() - height()/2.0);
//     //}
// }

// void Simulation::render(std::shared_ptr<sf::RenderWindow> window)
// {
//     // Draw background
//     window->draw(background);

//     //// Draw controls
//     //entitiesGroupControl->draw();
//     //foodsGroupControl->draw();
//     //onSimulationRenderTick(selectedModel);
// }

// // void Simulation::setOnEntityModelSelected(std::function<void(EntityModel*)> func)
// // {
// //     onEntityModelSelected = func;
// // }

// // void Simulation::setOnEntityModelDeselected(std::function<void(EntityModel*)> func)
// // {
// //     onEntityModelDeselected = func;
// // }

#include "simulation.hpp"

void Simulation::init()
{   
    // Window
    sf::Vector2u windowSize{unsigned(1000), unsigned(1000)};
    window = sf::RenderWindow(sf::VideoMode(windowSize), "ASLS");

    // UI
    // cellShape = sf::RectangleShape(sf::Vector2f{float(cellSize - 1), float(cellSize - 1)});
    // gui = std::make_unique<tgui::Gui>(window);
    // createGUI();

    // Group controls
    entitiesGroupControl = std::make_unique<Entities>();

    // Solver
    solver = std::make_unique<Solver>();
    solver->setOnEntityModelCreated([this](EntityModel* m) {entitiesGroupControl->buildControl(m);});
    solver->setOnEntityModelDeleted([this](EntityModel* m) {entitiesGroupControl->deleteControl(m);});

    // Brain
    brain = new Brain();
}

void Simulation::run()
{
    double previous = nowEpoch_s();
    double remaining_ms{0.0};
    while (window.isOpen())
    {
        // Compute time
        double current = nowEpoch_s();
        double elapsed_ms = current - previous;
        previous = current;
        remaining_ms += elapsed_ms;

        // Inputs
        handleInputs();

        while (remaining_ms >= dt_s)
        {
            // Models
            if (isPlaying)
            {
                update();
            }
            remaining_ms -= dt_s;
        }

        // Render
        render();
    }
}

void Simulation::handleInputs()
{
    while (auto evt = window.pollEvent())
    {
        // gui->handleEvent(*evt);
        
        if (evt->is<sf::Event::Closed>())
        {
            window.close();
        }
        else if (auto keyPressed = evt->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Space)
                isPlaying = !isPlaying;
        }
    }
}

void Simulation::update()
{
	// Update the models
	solver->solve(dt_s);

    if (solver->entities.size() > 0)
        brain->setSelectedGenome(solver->entities[0]->genome);
}

void Simulation::render()
{
    // Clear and Draw background
    window.clear(sf::Color::Black);

    // UI
    // gui->draw();
    entitiesGroupControl->draw(window);

    brain->drawGenome(window);

    // Display window
    window.display();
}

void Simulation::play()
{
    isPlaying = true;
}

void Simulation::pause()
{
    isPlaying = false;
}

double Simulation::nowEpoch_s()
{
    auto tp = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration<double>(tp).count();
}

// void Simulation::createGUI()
// {
//     // keep them alive in `this->…`
//     combo   = tgui::ComboBox::create();
//     loadBtn = tgui::Button::create("Load Pattern");
//     list    = tgui::ListBox::create();

//     // 1) Populate combo
//     combo->setPosition(10,10);
//     combo->setSize(200,25);
//     for (auto &kv : p_library->getPatterns())
//         combo->addItem(kv.first);
//     combo->setSelectedItemByIndex(0);
//     gui->add(combo);

//     // 2) Wire the Load button, capturing `this` so we can use `combo` and `p_grid`
//     loadBtn->setPosition(220,10);
//     loadBtn->setSize(120,25);
//     loadBtn->onPress([this]{
//         const auto name = combo->getSelectedItem().toStdString();
//         if (auto pat = p_library->get(name)) {
//             p_grid->clear();
//             int offR = rows/2 - 10;
//             int offC = cols/2 - 10;
//             p_grid->loadPattern(pat->cells, offR, offC);
//         }
//     });
//     gui->add(loadBtn);

//     // 3) Or use the ListBox to auto-load on select
//     list->setPosition(10,50);
//     list->setSize(200,80);
//     for (auto &kv : p_library->getPatterns())
//         list->addItem(kv.first);
//     list->onItemSelect([this](const tgui::String &sel){
//         p_grid->clear();
//         if (auto pat = p_library->get(sel.toStdString()))
//             p_grid->loadPattern(pat->cells, rows/2-10, cols/2-10);
//     });
//     gui->add(list);
// }
