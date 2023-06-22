#pragma once

#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

// **********************************************
// Global Screen Resolution - change these values
// **********************************************
static const int SCREEN_WIDTH = 1920;
static const int SCREEN_HEIGHT = 1080;

// *************************************
// Global Game Title - change this value
// *************************************
const std::string GAME_TITLE = "BLACKJACK";

// ****************************************************
// Global Initial Window Position - change these values
// ****************************************************
const int XPOS = SDL_WINDOWPOS_CENTERED;
const int YPOS = SDL_WINDOWPOS_CENTERED;


// ****************************************************
// Global Scale Factor - change these values
// ****************************************************
const float SIZE_SCALE = 0.5;

// ****************************************************
// Global Font - change these values
// ****************************************************
//const TTF_Font* myFont = NULL;