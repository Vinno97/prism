#pragma once

#include "Menu/Control.h"
#include "Renderer/Graphics/Models/Mesh.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include <vector>

namespace Menu {
	class Menu
	{
	public:
		Menu()=default;
		std::vector<Control> controls;
		std::shared_ptr<Renderer::Graphics::Models::Mesh> mesh;

		Menu(const Menu &other);
		Menu(Menu &&other);
		Menu& operator=(const Menu& other);
		Menu& operator=(Menu&& other);
		~Menu();
		void cleanup();
	};
}