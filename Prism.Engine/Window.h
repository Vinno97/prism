#pragma once
#include <SDL.h>
#include "InputManager.h"

namespace SDLFacade {
	class Window
	{
	public:
		Window();
		void init();
		InputManager getInputManager();
		void close();
		~Window();
	private:
		SDL_Window *winID;
	};
}

