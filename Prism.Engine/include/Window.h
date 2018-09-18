#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/glew.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <string>
#include "InputManager.h"

namespace SDLFacade {
	/// <summary>
	/// This class represents the SDL context.
	/// </summary>
	class Window
	{
	public:
		Window();
		
		/// <summary>
		/// Initializes a new SDL window/context
		/// </summary>
		void init(const char* title, const int width, const int height, const int x, const int y);
		
		/// <summary>
		/// Returns an inputmanager
		/// </summary>
		InputManager getInputManager();
		
		/// <summary>
		/// Prepares SDL window for opengl rendering. Requires for window to be initialized
		/// </summary>		
		/// <remarks>
		///  Make sure to set useCompatibilityProfile to true if you want use opengl 3.1 or above but wish to maintain backwards compatibility
		/// </remarks>
		void createOpenGLContext(int majorVersion, int minorVersion, bool useCompatibilityProfile);
		
		/// <summary>
		/// Destroys the window
		/// </summary>	
		void close();
		~Window();
	private:
		SDL_Window *gWindow;
		SDL_GLContext gContext;
	};
}

