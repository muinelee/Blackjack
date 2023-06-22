#pragma once

#include <vector>

#include "SDL.h"

#include "Scene.h"

class SceneManager
{
public:
	static SceneManager* getInstance();
	static void removeInstance();

	void update();
	void render();

	void addScene(Scene*);
	void changeScene(Scene*);
	void removeScene();

	Scene* getCurrentScene();

	void onKeyDown(SDL_Event&);
	void onKeyUp(SDL_Event&);

	void onMouseButtonUp(SDL_Event&);
	void onMouseButtonDown(SDL_Event&);
	void onMouseMove(SDL_Event&);

	void onControllerButtonDown(SDL_Event&);
	void onControllerButtonUp(SDL_Event&);
	void onControllerAxisMotion(SDL_Event&);

private:
	SceneManager() = default;
	~SceneManager();

	std::vector<Scene*> gameStates;

	static SceneManager* instance;
};