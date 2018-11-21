#include "Surface.h"

Surface::Surface(const char* path)
{
	this->surface = IMG_Load(path);
}

int Surface::width()
{
	return this->surface->w;
}

int Surface::height()
{
	return this->surface->h;
}

void* Surface::pixels()
{
	return this->surface->pixels;
}

int Surface::bytesperPixel()
{
	return surface->format->BytesPerPixel;
}
