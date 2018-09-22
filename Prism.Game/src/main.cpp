#pragma once
#include <iostream>
#include "Window.h"
#include "InputManager.h"
#include "Key.h"

//QQQ Remove this main method
int main(int argc, char ** argv) {
	Window window;
	InputManager inputManager;
	window.init("Prism", 1280, 720, 100, 100);
	window.createOpenGLContext(4, 1, true);
	while (!window.shouldClose()) {
		if (inputManager.isKeyPressed(Key::KEY_W)) {
			std::cout << "Key W is pressed!" << std::endl;
		}
	}
	return 0;
}