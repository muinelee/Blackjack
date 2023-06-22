#include "Text.h"

Text::Text(SDL_Renderer* r, std::string f, int x, int y, double a, SDL_RendererFlip flip) : Image(r, f, x, y, a, flip)
{
	filename = "";
}

Text::~Text()
{
	std::cout << "Removing text ..." << std::endl;
	SDL_DestroyTexture(texture);
}

void Text::load()
{
	texture = ResourceManager::getInstance()->load(renderer, filename);

	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
}