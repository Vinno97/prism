#pragma once
#include "Window.h"
#include "CoreRenderer.h"

//QQQ Remove this main method
int main(int argc, char ** argv) {
	SDLFacade::Window window;
	window.init("Prism", 1920, 1080, 100, 100);
	window.createOpenGLContext(4, 1, true);
	Renderer::CoreRenderer cr;
	cr.init();
	while (true) {
		cr.draw();
		window.swapScreen();
	}
	return 0;
}