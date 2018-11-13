#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/glew.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <string>
#include "InputManager.h"

/// <summary>
/// This class represents the SDL context.
/// </summary>
class Window
{
public:
	/// <summary>
	/// Initializes a new SDL window/context
	/// </summary>
	Window();

	/// <summary>
	/// Initializes a new SDL window/context
	/// </summary>
	void init(const char* title, const int width, const int height, const int x, const int y);

	/// <summary>
	/// Returns an inputmanager
	/// </summary>
	InputManager getInputManager();

	SDL_Window *getWindow();

	/// <summary>
	/// Prepares SDL window for opengl rendering. Requires for window to be initialized
	/// </summary>		
	/// <remarks>
	///  Make sure to set useCompatibilityProfile to true if you want use opengl 3.1 or above but wish to maintain backwards compatibility
	/// </remarks>
	void createOpenGLContext(int majorVersion, int minorVersion, bool useCompatibilityProfile);

	void swapScreen();

	/// <summary>
	/// Return true when the close button is pressed on the window
	/// </summary>
	bool shouldClose();

	/// <summary>
	/// Destroys the window
	/// </summary>	
	void close();

	int width;
	int height;

	~Window();
private:
	SDL_Window *gWindow;
	SDL_GLContext gContext;
};