#pragma once

#include <vector>

#include "GameObject.h"
#include "Game.h"
#include "Card.h"

class Deck : public GameObject
{
public:
	Deck();
	~Deck();

	void update();
	void render();

	void createCard();
	void shuffle();
	void layout();

private:
	std::vector<Card*> cards;
};