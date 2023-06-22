#pragma once

#include "Global.h"

#include "Game.h"
#include "Scene.h"
#include "Image.h"
#include "Button.h"
#include "InputManager.h"

class MenuScene : public Scene
{
public:
	MenuScene();

	void update();
	void render();

	bool onEnter();
	bool onExit();

	void onKeyDown(SDL_Event&);

	void onMouseButtonDown(SDL_Event&);
	void onMouseButtonUp(SDL_Event&);
	void onMouseMove(SDL_Event&);

private:
	Image* bg;
	Image* logo;

	Button* start;
};