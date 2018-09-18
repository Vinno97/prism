#pragma once
#include "Window.h"

//QQQ Remove this main method
int main(int argc, char ** argv) {
	SDLFacade::Window window;
	window.init("Prism", 1280, 720, 100, 100);
	window.createOpenGLContext(4, 1, true);
	while (true) {
	}
	return 0;
}