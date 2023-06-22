#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* r, std::string f, int x, int y, int w, int h, int rows, int cols, int offsetX, int offsetY, double a, SDL_RendererFlip flip) : renderer(r), filename(f), position(x, y), w(w), h(h), angle(a), offsetX(offsetX), offsetY(offsetY), flipFlag(flip)
{
	frameInfo.reserve(rows * cols);

	visible = true;
	isAnimating = false;

	currentFrame = 0;
	startFrame = 0;
	endFrame = 0;

	fps = 0;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			SDL_Rect temp;

			temp.x = (j * w) + offsetX;
			temp.y = (i * h) + offsetY;
			temp.w = w;
			temp.h = h;

			frameInfo.push_back(temp);
		}
	}

	load(f);

	startTime = SDL_GetTicks();
}

Sprite::~Sprite()
{
	std::cout << "Removing sprite " << filename << "..." << std::endl;
	SDL_DestroyTexture(texture);
}

void Sprite::load(std::string filename)
{
	texture = ResourceManager::getInstance()->load(renderer, filename);

	SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);
}

void Sprite::update()
{
	if (isAnimating)
	{
		Uint32 deltaTime = SDL_GetTicks() - startTime;

		currentFrame = ((((deltaTime * fps) / 1000) - startFrame) % ((endFrame + 1) - startFrame)) + startFrame;
	}
}

void Sprite::render()
{
	if (this->visible)
	{
		SDL_Rect source = frameInfo[currentFrame];
		SDL_Rect destination = getRect();

		SDL_RenderCopyEx(renderer, texture, &source, &destination, angle, nullptr, flipFlag);
	}
}

void Sprite::animate(int startFrame, int endFrame, int fps, bool flip)
{
	if (startFrame < 0 || endFrame >= frameInfo.size())
	{
		std::cout << "Animation out of range" << std::endl;
		return;
	}
	else
	{
		isAnimating = true;

		this->fps = fps;

		this->startFrame = startFrame;
		this->endFrame = endFrame;

		if (flip)
			flipFlag = SDL_FLIP_HORIZONTAL;
		else
			flipFlag = SDL_FLIP_NONE;
	}
}

void Sprite::gotoPos(int x, int y)
{
	position.x = x;
	position.y = y;
}

void Sprite::move(int deltaX, int deltaY)
{
	position.x += deltaX;
	position.y += deltaY;
}

SDL_Rect Sprite::getRect()
{
	return SDL_Rect{ static_cast<int>(position.x), static_cast<int>(position.y), (int)ceil(w * SIZE_SCALE), (int)ceil(h * SIZE_SCALE) };
}

void Sprite::setCurrentFrame(int frame)
{
	if (frame < 0 || frame >= frameInfo.size())
		currentFrame = 0;
	else
		currentFrame = frame;
}

int Sprite::getCurrentFrame()
{
	return currentFrame;
}

SDL_Texture* Sprite::getFrame()
{
	return texture;
}

bool Sprite::isVisible()
{
	return visible;
}

void Sprite::setVisible(bool visible)
{
	this->visible = visible;
}

Uint32 Sprite::getDelta()
{
	return SDL_GetTicks() - startTime;
}