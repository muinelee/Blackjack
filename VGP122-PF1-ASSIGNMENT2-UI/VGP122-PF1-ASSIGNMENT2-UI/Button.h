#pragma once
#include "Global.h"

#include "Game.h"
#include "Sprite.h"

class Button : public Sprite
{
public:
	Button(std::string f, int x, int y, int w, int h, int rows, int cols);

	void update();
	void render();

	void onPress();
	void onRelease();

	bool isPressed();

private:
	bool pressed;
};