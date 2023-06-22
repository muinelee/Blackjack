#include "InputManager.h"

InputManager::InputManager() : position(0, 0)
{ 
	init();
}

InputManager::~InputManager()
{
	for (int i = 0; i < controllers.size(); ++i)
		SDL_GameControllerClose(controllers[i]);
}

InputManager* InputManager::getInstance()
{
	if (instance == nullptr)
		instance = new InputManager();

	return instance;
}

void InputManager::removeInstance()
{
	if (instance != nullptr)
		delete instance;
}

void InputManager::init()
{
	position = Vector2D{ 0, 0 };

	for (int i = 0; i < 3; i++)
		mouseButtonStates.push_back(false);

	for (int i = 0; i < 22; ++i)
		controllerButtonStates.push_back(false);

	for (int i = 0; i < 6; ++i)
		controllerAxisStates.push_back(false);

	SDL_GameControllerAddMapping("4c05c405000000000000504944564944, PS4 Controller,a:b1,b:b2,back:b8,dpdown:h0.4,dpleft:h0.8,dpright:h0.2,dpup:h0.1,guide:b12,leftshoulder:b4,leftstick:b10,lefttrigger:a3,leftx:a0,lefty:a1,rightshoulder:b5,rightstick:b11,righttrigger:a4,rightx:a2,righty:a5,start:b9,touchpad:b13,x:b0,y:b3,");
	//SDL_GameControllerAddMappingsFromFile("SDL_GameControllerDB.txt");

	for (int i = 0; i < SDL_NumJoysticks(); ++i)
	{
		controllers[i] = SDL_GameControllerOpen(i);
		controllerStates.push_back(true);
		++numControllers;

		if (!controllers[i])
			std::cout << "Error: Controller not connected" << std::endl;
		else
		{
			if (SDL_JoystickEventState(SDL_ENABLE) < 0)
				std::cout << "Error: Joystick not initialized" << std::endl;

			if (SDL_GameControllerSetSensorEnabled(controllers[i], SDL_SENSOR_GYRO, SDL_TRUE) < 0)
				std::cout << "Error: Gyro not initialized" << std::endl;

			if (SDL_GameControllerSetSensorEnabled(controllers[i], SDL_SENSOR_ACCEL, SDL_TRUE) < 0)
				std::cout << "Error: Accellerometer not initialized" << std::endl;
		}

		ControllerAxis temp;

		temp.xAxis = 0;
		temp.yAxis = 0;
		temp.xDirection = 0;
		temp.yDirection = 0;

		controllerAxis.push_back(temp);
	}

	std::cout << "Input Manager Initialized..." << std::endl;
}

void InputManager::handleEvents()
{
	SDL_Event e;

	keystates = SDL_GetKeyboardState(0);

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		/*case SDL_QUIT:
			Game::getInstance()->stop();
			break;*/

		case SDL_KEYDOWN:
			onKeyDown(e);
			break;

		case SDL_KEYUP:
			onKeyUp(e);
			break;

		case SDL_MOUSEMOTION:
			onMouseMove(e);
			break;

		case SDL_MOUSEBUTTONDOWN:
			std::fill(mouseButtonStates.begin(), mouseButtonStates.end(), 0);
			onMouseButtonDown(e);
			break;

		case SDL_MOUSEBUTTONUP:
			std::fill(mouseButtonStates.begin(), mouseButtonStates.end(), 0);
			onMouseButtonUp(e);
			break;
		
		case SDL_CONTROLLERDEVICEADDED:
			std::cout << "Controller " << e.cdevice.which << " added..." << std::endl;
			if(SDL_IsGameController(e.cdevice.which) && !SDL_GameControllerGetAttached(controllers[e.cdevice.which]))
			{
				controllers[numControllers] = SDL_GameControllerOpen(numControllers);
				
				if (!controllers[numControllers])
					std::cout << "Error: Controller not connected" << std::endl;
				else
				{
					if (SDL_JoystickEventState(SDL_ENABLE) < 0)
						std::cout << "Error: Joystick not initialized" << std::endl;

					if (SDL_GameControllerSetSensorEnabled(controllers[numControllers], SDL_SENSOR_GYRO, SDL_TRUE) < 0)
						std::cout << "Error: Gyro not initialized" << std::endl;

					if (SDL_GameControllerSetSensorEnabled(controllers[numControllers], SDL_SENSOR_ACCEL, SDL_TRUE) < 0)
						std::cout << "Error: Accellerometer not initialized" << std::endl;
				}

				ControllerAxis temp;

				temp.xAxis = 0;
				temp.yAxis = 0;
				temp.xDirection = 0;
				temp.yDirection = 0;

				controllerAxis.push_back(temp);

				++numControllers;
				break;
			}

			break;

		case SDL_CONTROLLERDEVICEREMOVED:
			std::cout << "Controller " << e.cdevice.which << " removed..." << std::endl;
			SDL_GameControllerClose(controllers[e.cdevice.which]);
			--numControllers;
			break;

		case SDL_CONTROLLERBUTTONDOWN:
			std::fill(controllerButtonStates.begin(), controllerButtonStates.end(), 0);
			onControllerButtonDown(e);
			break;

		case SDL_CONTROLLERBUTTONUP:
			std::fill(controllerButtonStates.begin(), controllerButtonStates.end(), 0);
			onControllerButtonUp(e);
			break;

		case SDL_CONTROLLERAXISMOTION:
			std::fill(controllerAxisStates.begin(), controllerAxisStates.end(), 0);
			onControllerAxisMotion(e);
			break;

		default:
			break;
		}
	}
}

bool InputManager::isKeyDown(SDL_Scancode key)
{
	if (keystates != 0)
	{
		if (keystates[key] == 1)
			return true;
		else
			return false;
	}

	return false;
}

bool InputManager::getMouseButtonState(int buttonNum)
{
	return mouseButtonStates[buttonNum];
}

Vector2D InputManager::getMousePosition()
{
	return position;
}

int InputManager::getControllerButton()
{
	return controllerButton;
}

bool InputManager::getControllerButtonStates(int buttonNum)
{
	return controllerButtonStates[buttonNum];
}

bool InputManager::getControllerAxisStates(int axisNum)
{
	return controllerAxisStates[axisNum];
}

void InputManager::reset()
{
	for (int i = 0; i < mouseButtonStates.size(); i++)
		mouseButtonStates[i] = false;
}

void InputManager::onKeyDown(SDL_Event& e)
{
	std::cout << "Key Pressed: " << SDL_GetKeyName(e.key.keysym.sym) << std::endl;

	SceneManager::getInstance()->onKeyDown(e);
}

void InputManager::onKeyUp(SDL_Event& e)
{
	std::cout << "Key Released: " << SDL_GetKeyName(e.key.keysym.sym) << std::endl;

	SceneManager::getInstance()->onKeyUp(e);
}

void InputManager::onMouseMove(SDL_Event& e)
{
	position = Vector2D{ static_cast<float>(e.motion.x), static_cast<float>(e.motion.y) };

	std::cout << "Mouse position = x: " << position.x << ", y:" << position.y << std::endl;

	SceneManager::getInstance()->onMouseMove(e);
}

void InputManager::onMouseButtonDown(SDL_Event& e)
{
	if (e.button.button == SDL_BUTTON_LEFT)
	{
		mouseButtonStates[LEFT] = true;

		std::cout << "Left Mouse Button Pressed." << std::endl;
	}
	else if (e.button.button == SDL_BUTTON_MIDDLE)
	{
		mouseButtonStates[MIDDLE] = true;

		std::cout << "Middle Mouse Button Pressed." << std::endl;
	}
	else if (e.button.button == SDL_BUTTON_RIGHT)
	{
		mouseButtonStates[RIGHT] = true;

		std::cout << "Right Mouse Button Pressed." << std::endl;
	}

	SceneManager::getInstance()->onMouseButtonDown(e);
}

void InputManager::onMouseButtonUp(SDL_Event& e)
{
	if (e.button.button == SDL_BUTTON_LEFT)
	{
		mouseButtonStates[LEFT] = false;
		std::cout << "Left Mouse Button Released." << std::endl;
	}
	else if (e.button.button == SDL_BUTTON_MIDDLE)
	{
		mouseButtonStates[MIDDLE] = false;
		std::cout << "Middle Mouse Button Released." << std::endl;
	}
	else if (e.button.button == SDL_BUTTON_RIGHT)
	{
		mouseButtonStates[RIGHT] = false;
		std::cout << "Right Mouse Button Released." << std::endl;
	}

	SceneManager::getInstance()->onMouseButtonUp(e);
}

void InputManager::onControllerButtonDown(SDL_Event& e)
{
	std::cout << "Controller Button Pressed: " << SDL_GameControllerGetStringForButton((SDL_GameControllerButton)e.cbutton.button) << std::endl;

	controllerButton = (int)e.cbutton.button;
	controllerButtonStates[controllerButton] = true;

	SceneManager::getInstance()->onControllerButtonDown(e);
}

void InputManager::onControllerButtonUp(SDL_Event& e)
{
	std::cout << "Controller Button Released: " << SDL_GameControllerGetStringForButton((SDL_GameControllerButton)e.cbutton.button) << std::endl;

	controllerButton = (int)e.cbutton.button;

	SceneManager::getInstance()->onControllerButtonUp(e);
}

void InputManager::onControllerAxisMotion(SDL_Event& e)
{
	SDL_Joystick* j = SDL_GameControllerGetJoystick(controllers[e.cdevice.which]);
	SDL_JoystickID joyId = SDL_JoystickInstanceID(j);

	if (e.caxis.value < -JOYSTICK_DEADZONE || e.caxis.value > JOYSTICK_DEADZONE)
	{	
		if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX)
		{
			controllerAxisStates[LEFTX] = true;

			if (e.caxis.value < -JOYSTICK_DEADZONE)
				controllerAxis[joyId].xDirection = -1;
			else if (e.caxis.value > JOYSTICK_DEADZONE)
				controllerAxis[joyId].xDirection = 1;
			else
				controllerAxis[joyId].xDirection = 0;

			std::cout << "Controller Left X Axis Moved." << std::endl;
		}
		else if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY)
		{
			controllerAxisStates[LEFTY] = true;

			if (e.caxis.value < -JOYSTICK_DEADZONE)
				controllerAxis[joyId].yDirection = -1;
			else if (e.caxis.value > JOYSTICK_DEADZONE)
				controllerAxis[joyId].yDirection = 1;
			else
				controllerAxis[joyId].yDirection = 0;

			std::cout << "Controller Left Y Axis Moved." << std::endl;
		}
		else if (e.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX)
		{
			controllerAxisStates[RIGHTX] = true;

			if (e.caxis.value < -JOYSTICK_DEADZONE)
				controllerAxis[joyId].xDirection = -1;
			else if (e.caxis.value > JOYSTICK_DEADZONE)
				controllerAxis[joyId].xDirection = 1;
			else
				controllerAxis[joyId].xDirection = 0;

			std::cout << "Controller Right X Axis Moved." << std::endl;
		}
		else if (e.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY)
		{
			controllerAxisStates[RIGHTY] = true;

			if (e.caxis.value < -JOYSTICK_DEADZONE)
				controllerAxis[joyId].yDirection = -1;
			else if (e.caxis.value > JOYSTICK_DEADZONE)
				controllerAxis[joyId].yDirection = 1;
			else
				controllerAxis[joyId].yDirection = 0;

			std::cout << "Controller Right Y Axis Moved." << std::endl;
		}
		else if (e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT)
		{
			controllerAxisStates[TRIGGERLEFT] = true;

			std::cout << "Controller Trigger Left Moved." << std::endl;
		}
		else if (e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
		{
			controllerAxisStates[TRIGGERRIGHT] = true;

			std::cout << "Controller Trigger Right Moved." << std::endl;
		}

		SDL_Joystick* temp = SDL_GameControllerGetJoystick(controllers[joyId]);

		controllerAxis[joyId].xAxis = SDL_JoystickGetAxis(temp, 0);
		controllerAxis[joyId].yAxis = SDL_JoystickGetAxis(temp, 1);

		controllerAxis[joyId].angle = atan2((double)controllerAxis[joyId].yDirection, (double)controllerAxis[joyId].xDirection) * (180.0 / M_PI);

		if (controllerAxis[joyId].xDirection == 0 && controllerAxis[joyId].yDirection == 0)
			controllerAxis[joyId].angle = 0;

		SceneManager::getInstance()->onControllerAxisMotion(e);
	}
}

InputManager* InputManager::instance = nullptr;

int InputManager::numControllers = 0;
const int InputManager::JOYSTICK_DEADZONE = 8000;