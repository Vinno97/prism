#include "Window.h"
#include <iostream>
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <string>

namespace SDLFacade {
	Window::Window()
	{
	}

	void SDLFacade::Window::init(const char* title, const int width, const int height, const int x, const int y)
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		}

		gWindow = SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_SHOWN);
		if (gWindow == nullptr) {
			std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
		}
	}

	InputManager Window::getInputManager()
	{
		return InputManager();
	}

	void Window::createOpenGLContext(int majorVersion, int minorVersion, bool useCompatibilityProfile)
	{

		if (gWindow == nullptr) {
			std::cout << "SDL_Window does not exist. Has init() been called?" << std::endl;
			return;
		}

		bool success = true;	
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1); //Always set this to 1 obviousbly
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, majorVersion);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minorVersion);
		if (useCompatibilityProfile)
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
		else
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		gContext = SDL_GL_CreateContext(gWindow);
		if (gContext == NULL)
		{
			printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
		//	//Initialize GLEW
		//	bool glewExperimental = GL_TRUE;
		//	GLenum glewError = glewInit();
		//	if (glewError != GLEW_OK)
		//	{
		//		printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
		//	}

		//	//Use Vsync
		//	if (SDL_GL_SetSwapInterval(1) < 0)
		//	{
		//		printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
		//	}
		}
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
}