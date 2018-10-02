#pragma once
#include <iostream>
#include "Window.h"
#include "InputManager.h"
#include "Key.h"
#include "Renderer/TestRenderer.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//QQQ Remove this main method
int main(int argc, char ** argv) {

	Assimp::Importer importer;
	Window window;
	InputManager inputManager;
	window.init("Prism", 1920, 1080, 100, 100);
	window.createOpenGLContext(3, 2, true);
	Renderer::TestRenderer cr;
	cr.init();
	while (!window.shouldClose()) {
		if (inputManager.isKeyPressed(Key::KEY_W)) {
			std::cout << "Key W is pressed!" << std::endl;
		}
		cr.draw();
		window.swapScreen();
	}
	return 0;
}