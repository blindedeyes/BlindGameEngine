#pragma once
struct keyEventArg
{
	char key;
	bool state; 
};

class InputManager
{
	//Event list for key events
	std::vector<void(*)(keyEventArg&)> eventList;

	//frame based key input.
	bool currKeyStates[256];
	bool prevKeyStates[256];

public:
	InputManager();
	~InputManager();


};

