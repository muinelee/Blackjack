#include "Scene.h"

Scene::~Scene()
{
	std::map<int, GameObject*>::iterator it = gameObjects.begin();

	while(it != gameObjects.end())
	{
		std::cout << "Removing GameObject..." << std::endl;

		delete (*it).second;

		++it;
	}
}

void Scene::update()
{
	std::map<int, GameObject*>::iterator it = gameObjects.begin();

	while (it != gameObjects.end())
	{
		(*it).second->update();
		
		++it;
	}
}

void Scene::render()
{
	std::map<int, GameObject*>::iterator it = gameObjects.begin();

	while (it != gameObjects.end())
	{
		(*it).second->render();

		++it;
	}
}

void Scene::addGameObject(int depth, GameObject* object)
{
	std::cout << "Adding GameObject..." << std::endl;
	gameObjects[depth] = object;
}

bool Scene::onEnter()
{
	return true;
}

bool Scene::onExit()
{
	std::map<int, GameObject*>::iterator it = gameObjects.begin();

	while (it != gameObjects.end())
		gameObjects.erase(it);

	std::cout << "Exiting Scene..." << std::endl;

	return true;
}

/*Object* Scene::getObjectByID(std::string id)
{
	return gameObjects[id];
}*/