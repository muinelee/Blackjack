#pragma once

#include <cstdlib>
#include <ctime>

#include "SDL.h"
#include "SDL_Image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include "Window.h"
#include "Scene.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"

// Forward declaration - create Window first
class Window;
class InputManager;

class Game
{
public:
	Game() = default;
	~Game();

	// Singleton
	static Game* getInstance();
	
	void init(std::string, int, int, int, int, float, bool = false);

	// Game states
	void start();
	void stop();
	void pause();
	void resume();
	void shutdown();

	bool isRunning();
	bool isPaused();

	Uint32 getStartTime();
	Uint32 getDeltaTime();

	static SDL_Window* getWindow();
	static SDL_Renderer* getRenderer();

private:
	// Main game loop processing
	void handleEvents();
	void update();
	void render();
	void gameLoop();

	bool running;
	bool paused;

	// Initial game time and delta time
	Uint32 startTime = 0;
	Uint32 delta = 0;

	Window* window;
	InputManager* inputManager;
	SceneManager* sceneManager;

	static Game* instance;

	// Global frame rate
	static const float FPS;
	static const float DELAY_TIME;
};