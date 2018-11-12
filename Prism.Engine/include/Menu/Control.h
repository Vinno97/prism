#pragma once

#include "Renderer/Graphics/VertexArrayObject.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/Models/Model.h"

namespace Menu {
	class Control
	{
	public:
		Control() = default;
		Control(int x, int y, int width, int height);
		Renderer::Graphics::Models::Model model;
	};
}
