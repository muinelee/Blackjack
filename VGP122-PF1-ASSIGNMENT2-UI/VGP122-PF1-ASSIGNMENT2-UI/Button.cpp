#include "Button.h"

Button::Button(std::string f, int x, int y, int w, int h, int rows, int cols) : Sprite(Game::getRenderer(), f, x, y, w, h, rows, cols)
{
	pressed = false;

	setCurrentFrame(0);
}

void Button::update()
{
	Sprite::update();
}

void Button::render()
{
	Sprite::render();
}

void Button::onPress()
{
	pressed = true;
}

void Button::onRelease()
{
	pressed = false;
}

bool Button::isPressed()
{
	return pressed;
}