#pragma once

#include "Menu/Control.h"
#include "Menu/TextControl.h"
#include "Renderer/Graphics/Models/Mesh.h"
#include <vector>
#include <memory>
#include "InputManager.h"

namespace Menu {
	class Menu
	{
	public:
		Menu()=default;
		std::vector<std::unique_ptr<Control>> controls;
		std::vector<std::unique_ptr<TextControl>> textControls;
		std::shared_ptr<Renderer::Graphics::Models::Mesh> mesh;

		bool handleInput(InputManager& input, int height, int width, Context& context);

		~Menu();
		void cleanup();
	private:
		bool hit = false;
	};
}