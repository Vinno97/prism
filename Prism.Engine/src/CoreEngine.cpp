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
	this->forwardRenderer = new ForwardRenderer(1920, 1080);
}

//Runns the gameloop
void CoreEngine::Run() 
{
	//Holds the time in which the gameupdate was last called 
	auto lastTime = std::chrono::system_clock::now();
	int count = 0;

	ModelLoader ml = ModelLoader();
	Model* m = ml.loadModel("./res/bunny.obj");

	vector<Renderable> renderables;

	Renderable renderable;
	renderable.model = m;
	get<0>(renderable.position) = 0.f;
	get<1>(renderable.position) = -1.f;
	get<0>(renderable.scale) = 10;
	get<1>(renderable.scale) = 10;
	get<2>(renderable.scale) = 10;

	renderables.push_back(renderable);

	Renderable renderable1;
	renderable1.model = m;
	get<0>(renderable1.position) = 1.f;
	get<1>(renderable1.position) = 0.f;
	get<0>(renderable1.scale) = 15;
	get<1>(renderable1.scale) = 15;
	get<2>(renderable1.scale) = 15;

	renderables.push_back(renderable1);

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

		this->forwardRenderer->draw(renderables);

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
