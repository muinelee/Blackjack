#include "Card.h"

Card::Card(std::string f, int x, int y, int w, int h, int rows, int cols, int offsetx, int offsety, int face, int suit) 
	: Sprite(Game::getRenderer(), f, x, y, w, h, rows, cols, offsetx, offsety)
{

}