#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	renderer = nullptr;
}

ResourceManager::~ResourceManager()
{ }

ResourceManager* ResourceManager::getInstance()
{
	if (instance == nullptr)
		instance = new ResourceManager();

	return instance;
}

void ResourceManager::removeInstance()
{
	if (instance != nullptr)
		delete instance;
}

SDL_Texture* ResourceManager::load(SDL_Renderer* renderer, std::string filename)
{
	std::unordered_map<std::string, SDL_Texture*>::iterator it = resources.find(filename);

	if (it != resources.end())
	{
		std::cout << "Sprite " << filename << " already loaded..." << std::endl;
		return (*it).second;
	}

	SDL_Texture* texture = IMG_LoadTexture(renderer, filename.c_str());

	std::cout << "Loading sprite " << filename << "..." << std::endl;

	if (texture == nullptr)
	{
		std::cout << "Error: Unable to open sprite - " << IMG_GetError() << std::endl;
		return nullptr;
	}

	resources[filename] = texture;

	return texture;
}

SDL_Texture* ResourceManager::findResource(std::string filename)
{
	SDL_Texture* texture = resources[filename];
	
	if (texture == nullptr)
	{
		std::cout << "Error: Unable to find resource " << filename << std::endl;
		return nullptr;
	}

	return texture;
}

void ResourceManager::addGameObject(int depth, GameObject* o)
{
	gameObjects[depth] = o;
}

std::unordered_map<std::string, SDL_Texture*> ResourceManager::resources;
std::map<int, GameObject*> ResourceManager::gameObjects;
ResourceManager* ResourceManager::instance = nullptr;