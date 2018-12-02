#pragma once

#include "Menu/Control.h"
#include "Menu/TextControl.h"
#include "Renderer/Graphics/Models/Mesh.h"
#include <vector>
#include "InputManager.h"

namespace Menu {
	class Menu
	{
	public:
		Menu()=default;
		std::vector<Control> controls;
		std::vector<TextControl> textControls;
		std::shared_ptr<Renderer::Graphics::Models::Mesh> mesh;

		bool handleInput(InputManager& input, int height, int width);

		~Menu();
		void cleanup();
	};
}