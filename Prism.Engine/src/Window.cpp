#include "Window.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/glew.h>
#include <SDL2/SDL_opengl.h>
#include <cstdio>
#include <string>
#include "../lib/include/SDL2/SDL.h"

Window::Window()
	= default;

void Window::init(const char* title, const int width, const int height, const int x, const int y)
{
	this->width = width;
	this->height = height;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		}
	}
}

void Window::createOpenGLContext(const int majorVersion, const int minorVersion, const bool useCompatibilityProfile)
{

	if (gWindow == nullptr) {
		std::cout << "SDL_Window does not exist. Has init() been called?" << std::endl;
		throw "SDL_Window does not exist";
		return;
	}
	bool success = true;
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1); //Always set this to 1 obviousbly
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, majorVersion);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minorVersion);
	if (useCompatibilityProfile) {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	}
	else {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	}
	gContext = SDL_GL_CreateContext(gWindow);
	if (gContext == nullptr)
	{
		printf("OpenGL context could not be created! SDL Error: %s\n",
			SDL_GetError());
		success = false;
		throw "OpenGL Context could not be created";
	}
	else
	{
		//Initialize GLEW
		bool glewExperimental = GL_TRUE;
		GLenum glewError = glewInit();
		if (glewError != GLEW_OK)
		{
			printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
		}
		//Use Vsync
		if (SDL_GL_SetSwapInterval(1) < 0)
		{
			printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
		}
	}
}

void Window::swapScreen() {
	SDL_GL_SwapWindow(gWindow);
}

bool Window::setSize(const int newWidth, const int newHeight)
{	
	SDL_SetWindowSize(gWindow, newWidth, newHeight);
	return true;
}

bool Window::shouldClose()
{
	SDL_Event e;
	//Handle events on queue
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			this->close();
			return true;
		}
	}
	return false;
}

void Window::close()
{
	if (gWindow == nullptr) {
		std::cout << "Window was never initialized" << std::endl;
		SDL_DestroyWindow(gWindow);
	}
	SDL_Quit();
}

Window::~Window()
{
	close();
}