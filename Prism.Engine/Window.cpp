#include "Window.h"
#include <SDL.h>
#include <iostream>

namespace SDLFacade {
	Window::Window()
	{
	}

	void SDLFacade::Window::init()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		}

		winID = SDL_CreateWindow("BouncyBounce", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
		if (winID == nullptr) {
			std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
		}
	}

	InputManager Window::getInputManager()
	{
		return InputManager();
	}

	void Window::close()
	{
		if (winID == nullptr) {
			std::cout << "Window was never initialized" << std::endl;
			SDL_DestroyWindow(winID);
		}
		SDL_Quit();
	}

	Window::~Window()
	{
		if (winID == nullptr) {
			std::cout << "Window was never initialized" << std::endl;
			SDL_DestroyWindow(winID);
		}
		SDL_Quit();
	}
}