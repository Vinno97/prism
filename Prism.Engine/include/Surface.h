#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Surface
{
public:
	Surface(const char* path);
	int width();
	int height();
	void* pixels();
	int bytesperPixel();
private:
	SDL_Surface *surface;
};

