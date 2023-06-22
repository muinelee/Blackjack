#pragma once

#include <iostream>
#include <string>
#include <cmath>

#include "SDL.h"

#include "Game.h"
#include "SceneManager.h"

class Window
{
	// Game object can access private members of Window
	friend class Game;

public:
	// Singleton method to return instance
	static Window* getInstance(std::string, int, int, int, int, float, bool = false);
	
	// Singleton destructor
	static void removeInstance();

	static SDL_Window* getWindow();
	static SDL_Renderer* getRenderer();

private:
	Window(std::string, int, int, int, int, float, bool = false);
	~Window();

	// Main game loop update processing
	void update();

	// Main game loop render processing to window
	void render();

	int x;
	int y;
	int w;
	int h;
	float s;

	std::string title;
	bool fullScreen;

	static SDL_Window* window;
	static SDL_Renderer* renderer;

	// Singleton
	static Window* instance;
};