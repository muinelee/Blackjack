#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>

#include "SDL.h"

#include "Game.h"
#include "SceneManager.h"
#include "Vector2D.h"

typedef enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
} MOUSE_BUTTONS;

typedef enum controller_button_state
{
	A = 0,
	B = 1,
	X = 2,
	Y = 3,
	BACK = 4,
	GUIDE = 5, 
	START = 6, 
	LEFTSTICK = 7,
	RIGHTSTICK = 8,
	LEFTSHOULDER = 9,
	RIGHTSHOULDER = 10,
	DPADUP = 11,
	DPADDOWN = 12,
	DPADLEFT = 13,
	DPADRIGHT = 14,
	MISC1 = 15,
	PADDLE1 = 16,
	PADDLE2 = 17,
	PADDLE3 = 18,
	PADDLE4 = 19,
	TOUCHPAD = 20,
	MAX = 21
} CONTROLLER_BUTTON_STATE;

typedef enum controller_axis_state
{
	LEFTX = 0,
	LEFTY = 1,
	RIGHTX = 2,
	RIGHTY = 3,
	TRIGGERLEFT = 4,
	TRIGGERRIGHT = 5
} CONTROLLER_AXIS_STATE;

typedef struct controlleraxis
{
	int xAxis;
	int yAxis;
	int xDirection;
	int yDirection;
	double angle;
} ControllerAxis;

class InputManager
{
public:
	static InputManager* getInstance();
	static void removeInstance();

	void init();
	void handleEvents();

	bool isKeyDown(SDL_Scancode);

	bool getMouseButtonState(int);

	Vector2D getMousePosition();

	int getControllerButton();
	bool getControllerAxisStates(int);
	bool getControllerButtonStates(int);

	void reset();

	void onKeyDown(SDL_Event&);
	void onKeyUp(SDL_Event&);

	void onMouseMove(SDL_Event&);
	void onMouseButtonDown(SDL_Event&);
	void onMouseButtonUp(SDL_Event&);

	void onControllerButtonDown(SDL_Event&);
	void onControllerButtonUp(SDL_Event&);
	void onControllerAxisMotion(SDL_Event&);

private:
	InputManager();
	~InputManager();

	const Uint8* keystates;

	Vector2D position;
	std::vector<bool> mouseButtonStates;

	int controllerButton;
	std::vector<ControllerAxis> controllerAxis;
	std::unordered_map<int, SDL_GameController*> controllers;
	std::vector<bool> controllerStates;
	std::vector<bool> controllerButtonStates;
	std::vector<bool> controllerAxisStates;

	static InputManager* instance;
	static int numControllers;
	static const int JOYSTICK_DEADZONE;
};