#pragma once

#include "Global.h"

#include "Game.h"
#include "Scene.h"
#include "Image.h"
#include "Button.h"
#include "InputManager.h"

#include "Card.h"

class PlayScene : public Scene
{
public:
	PlayScene();

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
	Image* table;

	Button* hit;
	Button* stand;
	Button* pass;
	Button* dubble;
	Button* split;

	Card* card;
};