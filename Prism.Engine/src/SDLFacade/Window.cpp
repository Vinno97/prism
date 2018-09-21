#include "Window.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/glew.h>
#include <SDL2/SDL_opengl.h>
#include <cstdio>
#include <string>

namespace SDLFacade {
	Window::Window()
		= default;

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
}