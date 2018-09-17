#pragma once
#include "Window.h"

//QQQ Remove this main method
int main(int argc, char **argv) {
	SDLFacade::Window window;
	window.init();
	while (true);
	return 0;
}