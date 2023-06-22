#pragma once

#include "Global.h"

#include "Game.h"
#include "Sprite.h"

class Card : public Sprite
{
public:
	Card(std::string f, int x, int y, int w, int h, int rows, int cols, int offsetx, int offsety, int face, int suit);
};