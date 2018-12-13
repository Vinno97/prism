#pragma once
#include <GL/glew.h>
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/Pipeline.h"
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Menu/Menu.h"
#include "Menu/TextRenderer.h"

namespace Menu
{
	class MenuRenderer
	{
	public:
		MenuRenderer();
		void renderMenu(Menu& menu, float aspect);
	private:
		TextRenderer textRenderer;
		Renderer::Graphics::RenderDevice* renderDevice;
		std::unique_ptr<Renderer::Graphics::Pipeline> menuPipeline;
		glm::mat4 projection;
	};
}
