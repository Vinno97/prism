#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/VertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"
#include "Renderer/Graphics/VertexArrayObject.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Renderer/Graphics/Loader/ModelLoader.h"
#include "Renderer/Graphics/Models/Model.h"

using namespace Renderer::Graphics;

namespace Renderer {
	class ForwardRenderer
	{
	public:
		ForwardRenderer();
		~ForwardRenderer();
	private: 
		Pipeline* geometryPipeline;
		RenderDevice* renderDevice;
	};
}

