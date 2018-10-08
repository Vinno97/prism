#include "CoreEngine.h"
#include "Renderer/ForwardRenderer.h"
#include "Renderer/Graphics/Models/Model.h"
#include "Renderer/Graphics/Loader/ModelLoader.h"
#include <tuple>
#include <vector>
#include "Renderer/TestRenderer.h"
#include "ECS/EntityManager.h"
#include "ECS/Components/AppearanceComponent.h"
#include "Renderer/Graphics/Models/Model.h";
#include "ECS/Systems/RenderSystem.h"
#include "ECS/SystemManager.h"

using namespace Renderer;
using namespace std;
using namespace Renderer::Graphics::Models;
using namespace Renderer::Graphics::Loader;
using namespace ECS;
using namespace ECS::Components;
using namespace ECS::Systems;
using namespace Renderer::Graphics::Loader;


const void CoreEngine::InitWindow(const char* title, const int width, const int height, const int x, const int y) {
	context.window->init(title, width, height, x, y);
	context.window->createOpenGLContext(3, 2, true);
}

//Runns the gameloop
void CoreEngine::Run()
{
	//Holds the time in which the gameupdate was last called 
	auto lastTime = std::chrono::system_clock::now();
	int count = 0;

	Context c;

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
		auto currentState = context.stateMachine->getCurrentState();
		currentState->onUpdate(context);

		//Swap the screen buffer
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
