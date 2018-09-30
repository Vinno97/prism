#pragma once
#include <iostream>
#include "Window.h"
#include "ECS/EntityManager.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "InputManager.h"
#include "Key.h"
#include "ECS/SystemManager.h"
#include "ECS/RenderSystem.h"

#include "ECS/Components/Component.h"



#include <cstdlib>  
#include <crtdbg.h> 

// This function makes sure all objects are cleared from the stack before the memory gets dumped.

void start() 
{


}

int main(int argc, char ** argv) {
	start();
	_CrtDumpMemoryLeaks();
	return 0;
}