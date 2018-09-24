#include "Window.h"
#include "CoreRenderer.h"

//QQQ Remove this main method
int main(int argc, char ** argv) {
	Window window;
	window.init("Prism", 1280, 720, 100, 100);
	//window.createOpenGLContext(3, 1, true);

	Renderer::CoreRenderer coreRenderer;
	coreRenderer.init();
	while (true) {
		//coreRenderer.draw();
		//window.swapScreen();
	}
	return 0;
}
