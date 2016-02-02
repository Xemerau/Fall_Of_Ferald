#include "StateManager.h"
#include "GameState.h"
#include "MenuState.h"
#include <iostream>

StateManager::StateManager(InputManager* inputs, ImageManager* images, sf::RenderWindow* win)
{
	// Setting up our pointers
	inputManager = inputs;
	imageManager = images;
	window = win;


	// Creating the game state right off the bat, since it's all we have
	// implemented currently
	//pushState(StateEnum::GAME);
	pushState(StateEnum::MENU);
}

StateManager::StateManager()
{
	inputManager = NULL;
	imageManager = NULL;
	window = NULL;
}

StateManager::~StateManager()
{
	// Clearing our stack
	while(!stateStack.empty())
		popState();
}

void StateManager::pushState(StateEnum stateType)
{
	// Pausing the current state, if needed
	if(!stateStack.empty())
		stateStack.top()->onPause();

	// Creating a new state on top of the stack
	switch(stateType)
	{
		case GAME:
			std::cout << "\t Game State Created!" << std::endl;
			stateStack.emplace(new GameState());
			break;
		case MENU:
			std::cout << "\t Menu State Created!" << std::endl;
			stateStack.emplace(new MenuState());
			break;
		default:
			std::cout << "Cannot create state!" << std::endl;
			return;
	}

	stateStack.top()->onEnter(NULL, imageManager);
	currentState = stateType;
}


// Removing the current state from the top of the stack
void StateManager::popState()
{
	stateStack.top()->onExit(imageManager);
	delete stateStack.top();
	stateStack.pop();
}

// Switch states safely, removing the current state and emplacing a new one
// usually called from within the current state
void StateManager::switchState(StateEnum stateType)
{
	if(stateType == LOADING)
	{
		std::cout << std::endl;
		std::cout << "Please do not enter the loading state directly!" << std::endl;
		std::cout << "Switching states will invoke the loading state>" << std::endl;
		return;
	}
	stateStack.top()->onExit(imageManager);
	//TODO: Create a new state, call update and render

	delete stateStack.top();
	stateStack.pop();
	pushState(stateType);
}

// Returns false if we have no more states to update
bool StateManager::update()
{
	inputManager->update(*window);

	// Just being safe
	if(!stateStack.empty())
	{
		stateStack.top()->update(inputManager, this);
	} 

	// Rechecking since we may have exited from within the state
	return stateStack.empty();
}

void StateManager::render()
{
	if(!stateStack.empty() && window != NULL)
		stateStack.top()->render(window);
}
