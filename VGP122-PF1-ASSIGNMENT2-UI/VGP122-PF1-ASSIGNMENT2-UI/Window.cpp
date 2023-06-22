#include "Window.h"

// Initialize SDL and create window and renderer
Window::Window(std::string t, int x, int y, int w, int h, float s, bool full) : title(t), x(x), y(y), w(w), h(h), s(s), fullScreen(full)
{ 
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		Uint32 flags = 0;

		std::cout << "SDL initializing" << std::endl;

		if (full)
			 flags = SDL_WINDOW_FULLSCREEN;

		window = SDL_CreateWindow(title.c_str(), x, y, ceil(w*s), ceil(h*s), flags);

		if (window != 0)
		{
			std::cout << "Window created..." << std::endl;

			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (renderer != 0)
			{
				std::cout << "Renderer created..." << std::endl;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			}
			else
				std::cout << "Error: Renderer was not created" << std::endl;
		}
		else
			std::cout << "Error: Window was not created" << std::endl;
	}
	else
		std::cout << "Error: SDL was not initialized" << std::endl;
}

// Shurtdown SDL and unload window and renderer
Window::~Window()
{
	std::cout << "Shutting down SDL" << std::endl;

	if (renderer != nullptr)
	{
		std::cout << "Removing renderer..." << std::endl;
		SDL_DestroyRenderer(renderer);
	}
	else
		std::cout << "Error: Renderer could not be removed" << std::endl;

	if (window != nullptr)
	{
		std::cout << "Removing window..." << std::endl;
		SDL_DestroyWindow(window);
	}
	else
		std::cout << "Error: Window could not be removed" << std::endl;
}

// Singleton initialization
Window* Window::getInstance(std::string t, int x, int y, int w, int h, float s, bool full)
{
	if (instance == nullptr)
		instance = new Window(t, x, y, w, h, s, full);

	return instance;
}

// Singleton deletion
void Window::removeInstance()
{
	if (instance != nullptr)
		delete instance;
}

SDL_Window* Window::getWindow()
{
	return window;
}

SDL_Renderer* Window::getRenderer()
{
	return renderer;
}

// Main game loop update using user supplied function pointer
void Window::update()
{
	SceneManager::getInstance()->update();
}

// Main game loop render using user supplied function pointer and render to screen
void Window::render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderClear(renderer);

	// Call game object render method
	SceneManager::getInstance()->render();

	SDL_RenderPresent(renderer);
}

// Singleton initialization
Window* Window::instance = nullptr;

SDL_Window* Window::window = nullptr;
SDL_Renderer* Window::renderer = nullptr;