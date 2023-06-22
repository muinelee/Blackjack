#include "SceneManager.h"

SceneManager::~SceneManager()
{
	for (int i = 0; i < gameStates.size(); ++i)
		delete gameStates[i];
}

SceneManager* SceneManager::getInstance()
{
	if (instance == nullptr)
		instance = new SceneManager();

	return instance;
}

void SceneManager::removeInstance()
{
	if (instance != nullptr)
		delete instance;
}

void SceneManager::addScene(Scene* state)
{
	gameStates.push_back(state);

	gameStates.back()->onEnter();
}

void SceneManager::changeScene(Scene* state)
{
	if (!gameStates.empty())
			return;

	gameStates.push_back(state);

	if (!gameStates.empty())
		if (gameStates.back()->onExit())
			gameStates.erase(gameStates.end() - 2);

	gameStates.back()->onEnter();
}

void SceneManager::removeScene()
{
	if (!gameStates.empty())
		if (gameStates.back()->onExit())
			gameStates.erase(gameStates.end() - 1);
}

Scene* SceneManager::getCurrentScene()
{
	return gameStates.back();
}

void SceneManager::update()
{
	if (!gameStates.empty())
		gameStates.back()->update();
}

void SceneManager::render()
{
	if (!gameStates.empty())
		gameStates.back()->render();
}

void SceneManager::onKeyDown(SDL_Event& e)
{
	if (!gameStates.empty())
		gameStates.back()->onKeyDown(e);
}

void SceneManager::onKeyUp(SDL_Event& e)
{
	if (!gameStates.empty())
		gameStates.back()->onKeyUp(e);
}

void SceneManager::onMouseButtonDown(SDL_Event& e)
{
	if (!gameStates.empty())
		gameStates.back()->onMouseButtonDown(e);
}

void SceneManager::onMouseButtonUp(SDL_Event& e)
{
	if (!gameStates.empty())
		gameStates.back()->onMouseButtonUp(e);
}

void SceneManager::onMouseMove(SDL_Event& e)
{
	if (!gameStates.empty())
		gameStates.back()->onMouseMove(e);
}

void SceneManager::onControllerButtonDown(SDL_Event& e)
{
	if (!gameStates.empty())
		gameStates.back()->onControllerButtonDown(e);
}

void SceneManager::onControllerButtonUp(SDL_Event& e)
{
	if (!gameStates.empty())
		gameStates.back()->onControllerButtonUp(e);
}

void SceneManager::onControllerAxisMotion(SDL_Event& e)
{
	if (!gameStates.empty())
		gameStates.back()->onControllerAxisMotion(e);
}

SceneManager* SceneManager::instance = nullptr;