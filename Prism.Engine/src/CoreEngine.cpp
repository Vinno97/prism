#include "CoreEngine.h"
#include "Renderer/ForwardRenderer.h"
#include "Renderer/Graphics/Models/Model.h"
#include "Renderer/Graphics/Loader/ModelLoader.h"
#include <tuple>
#include <vector>

using namespace Renderer;
using namespace std;
using namespace Renderer::Graphics::Models;
using namespace Renderer::Graphics::Loader;

const void CoreEngine::CreateWindow(const char* title, const int width, const int height, const int x, const int y) {
	context.window->init(title, width, height, x, y);
	context.window->createOpenGLContext(3, 2, true);
}

//Runns the gameloop
void CoreEngine::Run() 
{
	//Holds the time in which the gameupdate was last called 
	auto lastTime = std::chrono::system_clock::now();
	int count = 0;

	Renderer::ForwardRenderer forwardRenderer = Renderer::ForwardRenderer(context.window->width, context.window->height);

	ModelLoader ml = ModelLoader();
	Model* m = ml.loadModel("./res/bunny.obj");

	vector<tuple<Model*, float, float, float>> renderables;

	for(float x = -12.f; x < 20; x++)
		renderables.push_back(tuple<Model*, float, float, float>(m, x/5, 0, 1));

	//While the window is unclosed run the gameloop
	while (!context.window->shouldClose()) 
	{
		//Holds the time in which the current gameupdat is being called
		auto startTime = std::chrono::system_clock::now();
		
		//Deltatime in microseconds
		auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(startTime - lastTime); 
		lastTime = startTime;

		//Sets the right values in context
		context.deltaTime = deltaTime.count();
		context.stateMachine->getCurrentState()->onUpdate(context);

		forwardRenderer.draw(renderables);

		//Swap the screen buffer
		context.window->swapScreen();
	}
}

void CoreEngine::CleanUp() {
	//Free memory
	delete context.stateMachine;
	delete context.window;
}

CoreEngine::~CoreEngine()
{
	CleanUp();
}
