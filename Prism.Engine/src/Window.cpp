#include "Window.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/glew.h>
#include <SDL2/SDL_opengl.h>
#include <cstdio>
#include <string>

Window::Window()
	= default;

void Window::init(const char* title, const int width, const int height, const int x, const int y)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		//Enable antialiasing
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
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
	if (gWindow == nullptr) {
		std::cout << "Window was never initialized" << std::endl;
		SDL_DestroyWindow(gWindow);
	}
	SDL_Quit();
}