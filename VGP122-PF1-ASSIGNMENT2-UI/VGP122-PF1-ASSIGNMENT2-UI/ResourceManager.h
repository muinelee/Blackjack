#pragma once

#include <string>
#include <map>
#include <unordered_map>

#include "SDL.h"
#include "SDL_image.h"

#include "GameObject.h"
#include "Sprite.h"

class ResourceManager
{
public:
	~ResourceManager();

	static ResourceManager* getInstance();
	static void removeInstance();

	SDL_Texture* load(SDL_Renderer*, std::string);
	SDL_Texture* findResource(std::string filename);

	void addGameObject(int, GameObject*);

	static std::unordered_map<std::string, SDL_Texture*> resources;
	static std::map<int, GameObject*> gameObjects;


private:
	ResourceManager();

	SDL_Renderer* renderer;

	static ResourceManager* instance;
};