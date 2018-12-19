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
#include "Menu/MenuBuilder.h"
#include "Menu/Menu.h"
#include "Menu/MenuRenderer.h"

using namespace std;
using namespace Menu;
using namespace Renderer::Graphics::Loader;

CoreEngine::CoreEngine()
{
	context.window = new Window();
	context.stateMachine = new StateMachine();
	context.inputManager = new InputManager();
	context.audioManager = new AudioManager();
}

const void CoreEngine::InitWindow(const char* title, const int width, const int height, const int x, const int y) {
	context.window->init(title, width, height, x, y);
	context.window->createOpenGLContext(3, 2, true);
}

//Runns the gameloop
void CoreEngine::Run()
{	
	

	//Holds the time in which the gameupdate was last called 
	auto lastTime = std::chrono::system_clock::now();

	// Holds the time when the was started
	auto gameStarted = std::chrono::system_clock::now();

	int count = 0;

	//Current State
	State * currentState = nullptr;

	//While the window is unclosed run the gameloop
	while (!context.window->shouldClose())
	{
		//Holds the time in which the current gameupdate is being called
		auto startTime = std::chrono::system_clock::now();
		auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(startTime - lastTime);
		lastTime = startTime;
		//Sets the right values in context
		context.deltaTime = deltaTime.count() / 1000000.f;

		//Check if state is changed
		if (context.stateMachine->getCurrentState() != currentState) {
			if (currentState != nullptr) {
				currentState->leave(context);
			}
			currentState = context.stateMachine->getCurrentState();
			if (!currentState->isInitialized()) {
				currentState->init(context);
			}
			currentState->enter(context);
			context.deltaTime = 0;
			lastTime = std::chrono::system_clock::now();
		}

		context.stateMachine->destroyEolStates(context);


		currentState->update(context);
	}
}

void CoreEngine::CleanUp() {
	//Free memory
	delete context.stateMachine;
	delete context.window;
	delete context.inputManager;
	delete context.audioManager;
}

CoreEngine::~CoreEngine()
{
	CleanUp();
}
