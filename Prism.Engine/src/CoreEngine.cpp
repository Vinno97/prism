#include "CoreEngine.h"
#include "Renderer/Graphics/Models/Model.h"
#include "Renderer/Renderable.h"
#include "Renderer/Graphics/Loader/ModelLoader.h"
#include "Renderer/ForwardRenderer.h"
#include "Renderer/Camera.h"
#include <tuple>
#include <memory>
#include <vector>

using namespace std;
using namespace Renderer::Graphics::Loader;
using namespace Renderer::Graphics::Models;
using namespace Renderer;


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

	ModelLoader ml = ModelLoader();
	shared_ptr<Model> m = ml.loadModel("./res/bunny.obj");

	vector<Renderable> renderables;

	//Test code
	//Add 3 bunnies at different positions in the world
	Renderable renderable;
	renderable.model = m.get();
	get<0>(renderable.position) = 0.f;
	get<1>(renderable.position) = -1.f;
	get<2>(renderable.position) = -6.f;
	get<0>(renderable.scale) = 10;
	get<1>(renderable.scale) = 10;
	get<2>(renderable.scale) = 10;
	get<1>(renderable.rotation) = 180.f;
	//Add to renderables
	renderables.push_back(renderable);

	//change position
	get<0>(renderable.position) = -2.f;
	get<1>(renderable.position) = -1.f;
	get<2>(renderable.position) = -3.f;
	renderables.push_back(renderable);

	get<0>(renderable.position) = 2.f;
	get<1>(renderable.position) = -1.f;
	get<2>(renderable.position) = -3.f;
	renderables.push_back(renderable);

	ForwardRenderer* fw = new ForwardRenderer(1920, 1080);
	Camera c = Camera();
	c.move(0.0f, 0.0f, 3.f);

	//While the window is unclosed run the gameloop
	while (!context.window->shouldClose()) 
	{
		//Holds the time in which the current gameupdat is being called
		auto startTime = std::chrono::system_clock::now();
		//Deltatime in microseconds
		auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(startTime - lastTime); 
		lastTime = startTime;
		//c.rotate(0.0f, 3.14f, 0.f);
		//Sets the right values in context
		context.deltaTime = deltaTime.count();

		//Swap the screen buffer
		context.stateMachine->getCurrentState()->onUpdate(context);
		fw->draw(&c, renderables);
		context.window->swapScreen();

	}
}

void CoreEngine::CleanUp() {
	//Free memory
	delete context.stateMachine;
	delete context.window;
	delete context.inputManager;
}

CoreEngine::~CoreEngine()
{
	CleanUp();
}
