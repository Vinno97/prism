#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <tuple>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Renderable.h"
#include "Renderer/Camera.h"
#include "Renderer/Graphics/VertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"
#include "Renderer/Graphics/VertexArrayObject.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Renderer/Graphics/Loader/ModelLoader.h"
#include "Renderer/Graphics/Models/Model.h"

namespace Renderer {
	class ForwardRenderer
	{
	public:
		ForwardRenderer(int width, int height);
		
		/// <summary>
		/// Draws the list of renderables from the viewpoint of a given camera
		/// </summary>
		void draw(Camera* camera, vector<Renderable> renderables);

		~ForwardRenderer();
	private: 
		glm::mat4 projection = glm::mat4(1.0f);

		unique_ptr<Pipeline> geometryPipeline;
		RenderDevice* renderDevice;
	};
}

