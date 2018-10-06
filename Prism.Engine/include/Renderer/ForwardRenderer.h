#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <tuple>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Renderable.h"
#include "Renderer/Graphics/VertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"
#include "Renderer/Graphics/VertexArrayObject.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Renderer/Graphics/Loader/ModelLoader.h"
#include "Renderer/Graphics/Models/Model.h"

using namespace Renderer::Graphics;
using namespace std;

namespace Renderer {
	class ForwardRenderer
	{
	public:
		ForwardRenderer(int width, int height);
		
		void draw(vector<Renderable> renderables);

		~ForwardRenderer();
	private: 
		glm::mat4 camera = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		glm::mat4 model = glm::mat4(0.0f);

		shared_ptr<Pipeline> geometryPipeline;
		RenderDevice* renderDevice;
	};
}

