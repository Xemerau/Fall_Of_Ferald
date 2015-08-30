#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "ImageManager.h"
#include "Level.h"
#include "Pathfinder.h"
#include "InputManager.h"
#include "UserInterface.h"
#include "AI.h"
#include <iostream>
#include <list>

class Game
{
    public:
        Game();
        virtual ~Game();
        void run();
        void render();
        void update();
    private:
        ImageManager imageManager;
		InputManager inputManager;
        sf::RenderWindow window;
		sf::Event event;
		UserInterface ui;
        Level* testLevel;
		sf::View camera;

		bool close = false;
        bool turnPassed = false;    // Flag to stop the AI from taking multiple turns

        // AI test vars
        /*std::list<Unit> testUnits();
        Unit testUnit("testUnit", "mage", 20, 5, 0, 2, 4, 3, 6, 5, 0);*/
};

#endif // GAME_H