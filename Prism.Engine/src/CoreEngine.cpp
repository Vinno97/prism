#include "CoreEngine.h"
#include "Renderer/Graphics/Models/Model.h"
#include "Renderer/Renderable.h"
#include "Renderer/Graphics/Loader/ModelLoader.h"
#include "Renderer/ForwardRenderer.h"
#include "Renderer/Camera.h"
#include <tuple>
#include <memory>
#include <vector>
#include "ECS/EntityManager.h"
#include "ECS/Components/AppearanceComponent.h"
#include "Renderer/Graphics/Models/Model.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/SystemManager.h"
#include "MenuBuilder.h"

using namespace std;
using namespace Renderer::Graphics::Loader;

const void CoreEngine::InitWindow(const char* title, const int width, const int height, const int x, const int y) {
	context.window->init(title, width, height, x, y);
	context.window->createOpenGLContext(3, 2, true);
}

//Runns the gameloop
void CoreEngine::Run()
{
	//TODO: Uit coreEngine verwijderen?
	MenuBuilder menuBuilder;

	//Holds the time in which the gameupdate was last called 
	auto lastTime = std::chrono::system_clock::now();
	int count = 0;

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
		context.deltaTime = deltaTime.count() / 1000000.f;
		context.stateMachine->getCurrentState()->onUpdate(context);
		
		//TODO: Verplaatsen? In ieder geval aanpassen.
		menuBuilder.DrawInGameOverlay(context.window->width, context.window->height);
		// ---

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
