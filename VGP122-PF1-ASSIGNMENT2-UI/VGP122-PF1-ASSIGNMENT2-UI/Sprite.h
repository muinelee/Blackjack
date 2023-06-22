#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "Global.h"

#include "GameObject.h"
#include "ResourceManager.h"
#include "Vector2D.h"

class Sprite : public GameObject
{
public:
	Sprite(SDL_Renderer*, std::string, int, int, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0, double = 0.0, SDL_RendererFlip = SDL_FLIP_NONE);
	~Sprite();

	virtual void update();
	virtual void render();

	void animate(int, int, int, bool = SDL_FLIP_NONE);
	void move(int, int);
	void gotoPos(int, int);

	SDL_Rect getRect();

	void setCurrentFrame(int);
	int getCurrentFrame();

	SDL_Texture* getFrame();
	
	bool isVisible();
	void setVisible(bool);

	Uint32 getDelta();

	SDL_RendererFlip flipFlag;

	Vector2D position;
	int w;
	int h;
	double angle;

protected:
	void load(std::string);

	int currentFrame;
	int startFrame;
	int endFrame;

	int fps;
	Uint32 startTime;

	bool isAnimating;

	SDL_Texture* texture;
	std::vector<SDL_Rect> frameInfo;
	
	int textureWidth;
	int textureHeight;

	int offsetX;
	int offsetY;

	bool visible;

	std::string filename;

	SDL_Renderer* renderer;
};