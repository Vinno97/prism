#pragma once
#include <iostream>
#include "Window.h"
#include "Key.h"

//QQQ Remove this main method
int main(int argc, char ** argv) {
	SDLFacade::Window window;
	window.init("Prism", 1280, 720, 100, 100);
	window.createOpenGLContext(4, 1, true);
	while (!window.shouldClose()) {
		if (window.getInputManager().isKeyPressed(Key::KEY_W)) {
			std::cout << "Key W is pressed!" << std::endl;
		}
	}
	return 0;
}