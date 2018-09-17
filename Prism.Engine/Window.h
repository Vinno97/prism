#pragma once
#include <iostream>
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <string>
#include "InputManager.h"

namespace SDLFacade {
	class Window
	{
	public:
		Window();
		void init(const char* title, const int width, const int height, const int x, const int y);
		InputManager getInputManager();
		void createOpenGLContext(int majorVersion, int minorVersion, bool useCompatibilityProfile);
		void close();
		~Window();
	private:
		SDL_Window *gWindow;
		SDL_GLContext gContext;
	};
}

