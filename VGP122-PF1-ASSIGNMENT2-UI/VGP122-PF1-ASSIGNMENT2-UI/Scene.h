#pragma once

#include <iostream>
#include <string>
#include <map>

#include "SDL.h"

#include "GameObject.h"

class Scene
{
public:
	virtual ~Scene();

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual void onKeyDown(SDL_Event&) { };
	virtual void onKeyUp(SDL_Event&) { };

	virtual void onMouseButtonDown(SDL_Event&) { };
	virtual void onMouseButtonUp(SDL_Event&) { };
	virtual void onMouseMove(SDL_Event&) { };

	virtual void onControllerButtonDown(SDL_Event&) { };
	virtual void onControllerButtonUp(SDL_Event&) { };
	virtual void onControllerAxisMotion(SDL_Event&) { };

	//virtual std::string getSceneID() const { };

	void addGameObject(int, GameObject*);
	//Object* getObjectByID(std::string);

	std::map<int, GameObject*> gameObjects;

protected:
	Scene() = default;
};