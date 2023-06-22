#pragma once

#include <iostream>
#include <string>
#include <cmath>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "Global.h"

#include "Image.h"
#include "Vector2D.h"
#include "ResourceManager.h"

class Text : public Image
{
	Text(SDL_Renderer*, std::string, int, int, double = 0.0, SDL_RendererFlip = SDL_FLIP_NONE);
	~Text();

	void load() override;
};