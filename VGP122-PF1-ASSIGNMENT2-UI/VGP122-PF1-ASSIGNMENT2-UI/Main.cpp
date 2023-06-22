#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "Global.h"

#include "Game.h"
#include "GameObject.h"
#include "SceneManager.h"

#include "MenuScene.h"
#include "PlayScene.h"

int main(int argv, char** argc)
{
	Game* game = Game::getInstance();

	// ********************************************
	// Game Initialization - add your settings here
	// ********************************************
	game->init(GAME_TITLE, XPOS, YPOS, SCREEN_WIDTH, SCREEN_HEIGHT, SIZE_SCALE);

	// *********************************
	// Game Scene - add your scenes here
	// *********************************
	SceneManager::getInstance()->addScene(new PlayScene());
	SceneManager::getInstance()->addScene(new MenuScene());

	game->start();
	
	game->shutdown();

	return 0;
}