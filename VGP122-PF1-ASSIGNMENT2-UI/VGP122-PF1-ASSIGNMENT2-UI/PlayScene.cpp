#include "PlayScene.h"

PlayScene::PlayScene()
{
	bg = new Image(Game::getRenderer(), "images/bg.png", 0, 0);
	table = new Image(Game::getRenderer(), "images/table.png", 0, 0);

	hit = new Button("images/buttons.png", 0, 0, 247, 108, 1, 6);
	stand = new Button("images/buttons.png", 0, 0, 247, 108, 1, 6);
	pass = new Button("images/buttons.png", 0, 0, 247, 108, 1, 6);
	dubble = new Button("images/buttons.png", 0, 0, 247, 108, 1, 6);
	split = new Button("images/buttons.png", 0, 0, 247, 108, 1, 6);

	card = new Card("images/cards.png", 0, 0, 225, 319, 6, 9, 11, 12, 0, 0);
	card->setCurrentFrame(2);

	table->position.x = ((SCREEN_WIDTH / 2) - (table->w / 2)) * SIZE_SCALE;
	table->position.y = (SCREEN_HEIGHT - table->h) * SIZE_SCALE;

	hit->position = { 325*SIZE_SCALE, (SCREEN_HEIGHT - hit->h)*SIZE_SCALE };
	hit->setCurrentFrame(1);

	stand->position = { 580 * SIZE_SCALE, (SCREEN_HEIGHT - stand->h) * SIZE_SCALE };
	stand->setCurrentFrame(2);

	pass->position = { 835 * SIZE_SCALE, (SCREEN_HEIGHT - pass->h) * SIZE_SCALE };
	pass->setCurrentFrame(3);

	dubble->position = { 1090 * SIZE_SCALE, (SCREEN_HEIGHT - dubble->h) * SIZE_SCALE };
	dubble->setCurrentFrame(4);

	split->position = { 1345 * SIZE_SCALE, (SCREEN_HEIGHT - split->h) * SIZE_SCALE };
	split->setCurrentFrame(5);
}

void PlayScene::update()
{
	Scene::update();

	if (hit->isPressed())
	{
		hit->onRelease();
		std::cout << "HIT" << std::endl;
	}
	
	if (stand->isPressed())
	{
		stand->onRelease();
		std::cout << "STAND" << std::endl;
	}

	if (pass->isPressed())
	{
		pass->onRelease();
		std::cout << "PASS" << std::endl;
	}

	if (dubble->isPressed())
	{
		dubble->onRelease();
		std::cout << "DOUBLE DOWN" << std::endl;
	}

	if (split->isPressed())
	{
		split->onRelease();
		std::cout << "SPLIT" << std::endl;
	}
}

void PlayScene::render()
{
	Scene::render();
}

bool PlayScene::onEnter()
{
	addGameObject(0, bg);
	addGameObject(1, table);
	addGameObject(2, hit);
	addGameObject(3, stand);
	addGameObject(4, pass);
	addGameObject(5, dubble);
	addGameObject(6, split);

	addGameObject(7, card);

	return true;
}

bool PlayScene::onExit()
{
	return true;
}

void PlayScene::onKeyDown(SDL_Event& e)
{
	InputManager* inputManager = InputManager::getInstance();

	if (inputManager->isKeyDown(SDL_SCANCODE_Q))
		Game::getInstance()->stop();
	else if (inputManager->isKeyDown(SDL_SCANCODE_P))
	{
		if(!Game::getInstance()->isPaused())
			Game::getInstance()->pause();
		else
			Game::getInstance()->resume();
	}
}

void PlayScene::onMouseButtonDown(SDL_Event& e)
{ 
	InputManager* inputManager = InputManager::getInstance();

	Vector2D mousePosition = inputManager->getMousePosition();

	if (mousePosition.x >= hit->position.x &&
		mousePosition.x <= hit->position.x + (hit->w * SIZE_SCALE) &&
		mousePosition.y >= hit->position.y &&
		mousePosition.y <= hit->position.y + (hit->h * SIZE_SCALE))
		hit->onPress();
	else if (mousePosition.x >= stand->position.x &&
		mousePosition.x <= stand->position.x + (stand->w * SIZE_SCALE) &&
		mousePosition.y >= stand->position.y &&
		mousePosition.y <= stand->position.y + (stand->h * SIZE_SCALE))
		stand->onPress();
	else if (mousePosition.x >= pass->position.x &&
		mousePosition.x <= pass->position.x + (pass->w * SIZE_SCALE) &&
		mousePosition.y >= pass->position.y &&
		mousePosition.y <= pass->position.y + (pass->h * SIZE_SCALE))
		pass->onPress();
	else if (mousePosition.x >= dubble->position.x &&
		mousePosition.x <= dubble->position.x + (dubble->w * SIZE_SCALE) &&
		mousePosition.y >= dubble->position.y &&
		mousePosition.y <= dubble->position.y + (dubble->h * SIZE_SCALE))
		dubble->onPress();
	else if (mousePosition.x >= split->position.x &&
		mousePosition.x <= split->position.x + (split->w * SIZE_SCALE) &&
		mousePosition.y >= split->position.y &&
		mousePosition.y <= split->position.y + (split->h * SIZE_SCALE))
		split->onPress();
}

void PlayScene::onMouseButtonUp(SDL_Event& e) 
{ }

void PlayScene::onMouseMove(SDL_Event& e)
{ }