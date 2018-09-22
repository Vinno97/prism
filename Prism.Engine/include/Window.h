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
	Window();
	
	/// <summary>
	/// Initializes a new SDL window/context
	/// </summary>
	/// <param name="title">Title that will appear in the upper left corner of the window.</param>
	/// <param name="width">Width of the window represented in pixels.</param>
	/// <param name="height">Height of the window represented in pixels.</param>
	/// <param name="x">Horizontal position of the window represented in pixels relative to the upper left corner of the screen.</param>
	/// <param name="y">Vertical position of the window represented in pixels relative to the upper left corner of the screen.</param>
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
	/// <param name="majorVersion">The major version of OpenGL to use.</param>
	/// <param name="minorVersion">The minor version of OpenGL to use.</param>
	/// <param name="useCompatibilityProfile">Enables/disables the usage of useCompatibiliyProfile so OpenGL 3.1+ can be utilized with backwards compatibility.</param>
	void createOpenGLContext(const int majorVersion, const int minorVersion, const bool useCompatibilityProfile);
	
	/// <summary>
	/// Return true when the close button is pressed on the window
	/// </summary>
	bool shouldClose();

	/// <summary>
	/// Destroys the window
	/// </summary>	
	void close();

	~Window();
private:
	SDL_Window *gWindow;
	SDL_GLContext gContext;
};

