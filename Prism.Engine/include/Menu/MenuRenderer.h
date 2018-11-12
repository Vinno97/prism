#pragma once

#include "Menu/Menu.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/Pipeline.h"
#include <memory>

namespace Menu {
	class MenuRenderer
	{
	public:
		MenuRenderer();
		void renderMenu(Menu& menu);
	private:
		Renderer::Graphics::RenderDevice* renderDevice;
		std::unique_ptr<Renderer::Graphics::Pipeline> menuPipeline;
	};
}
