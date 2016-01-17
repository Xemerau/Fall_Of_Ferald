#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include "BaseState.h"
#include "InputManager.h"
#include "ImageManager.h"
#include <stack>
class StateManager
{
public:
	enum StateEnum {MENU, OPTIONS, LOADING, GAME, COMBAT};

	StateManager(InputManager* inputs, ImageManager* images);
	~StateManager();
	StateManager();
	void pushState(StateEnum stateType);

	// Pop the current state and push a new state to the stack
	void switchState(StateEnum stateType);
private:
	void popState();

	std::stack<BaseState> stateStack;
	StateEnum currentState;
	InputManager* inputManager;
	ImageManager* imageManager;
	sf::RenderWindow* window;
};
#endif //STATEMANAGER_H