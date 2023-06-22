#include "Game.h"

// Shutdown game
Game::~Game()
{	
	SceneManager::removeInstance();
	ResourceManager::removeInstance();
	InputManager::removeInstance();
	Window::removeInstance();

	SDL_Quit();
}

Game* Game::getInstance()
{
	if (instance == nullptr)
		instance = new Game();

	return instance;
}

// Initialize game
void Game::init(std::string title, int x, int y, int w, int h, float s, bool flags)
{
	srand(static_cast<unsigned>(time(0)));

	running = false;
	paused = false;

	window = Window::getInstance(title, x, y, w, h, s, flags);
	inputManager = InputManager::getInstance();
	sceneManager = SceneManager::getInstance();
}

// Update events
void Game::handleEvents()
{
	inputManager->handleEvents();
}

// Update game logic
void Game::update()
{
	if(!isPaused())
		window->update();
}

// Render to screen
void Game::render()
{
	if (!isPaused())
		window->render();
}

// Start game and main game loop
void Game::start()
{
	running = true;
	paused = false;

	gameLoop();
}

// Stop main game loop
void Game::stop()
{
	running = false;
}

// Pause main game loop
void Game::pause()
{
	paused = true;
}

// Resume game loop from pause
void Game::resume()
{
	paused = false;
}

void Game::shutdown()
{
	running = false;
	paused = false;

	if (instance != nullptr)
		delete instance;
}

void Game::gameLoop()
{
	while (isRunning())
	{
		startTime = SDL_GetTicks();

		handleEvents();
		update();
		render();

		delta = SDL_GetTicks() - startTime;

		if (delta < DELAY_TIME)
			SDL_Delay((DELAY_TIME - delta));
	}
}

bool Game::isRunning()
{
	return running;
}

bool Game::isPaused()
{
	return paused;
}

SDL_Window* Game::getWindow()
{
	return Window::getWindow();
}

SDL_Renderer* Game::getRenderer()
{
	return Window::renderer;
}

Uint32 Game::getStartTime()
{
	return startTime;
}

Uint32 Game::getDeltaTime()
{
	return delta;
}

// Set frame rate
const float Game::FPS = 60.0f;
const float Game::DELAY_TIME = 1000.0f / FPS;

Game* Game::instance = nullptr;