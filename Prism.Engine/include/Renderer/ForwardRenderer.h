#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <tuple>
#include <memory>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Renderable.h"
#include "Renderer/Camera.h"
#include "Renderer/Graphics/VertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/RenderTarget.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"
#include "Renderer/Graphics/VertexArrayObject.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Renderer/Graphics/Texture.h"
#include "Renderer/Graphics/Models/Mesh.h"
#include "Renderer/Graphics/Loader/ModelLoader.h"
#include "Renderer/Graphics/Models/Model.h"
#include "Renderer/DirectionalLight.h"
#include "Renderer/Scene.h"

namespace Renderer {
	class ForwardRenderer
	{
	public:
		ForwardRenderer(int width, int height);
		
		/// <summary>
		/// Draws the list of renderables from the viewpoint of a given camera
		/// </summary>
		void draw(const Camera& camera, const std::vector<Renderable>& renderables, const Renderer::Scene& scene);

		int width;
		int height;
	private: 
		void createTargetQuad();
		void loadPipelines();

		glm::mat4 projection = glm::mat4(1.0f);
		std::unique_ptr<Renderer::Graphics::Pipeline> geometryPipeline;
		std::unique_ptr<Renderer::Graphics::Pipeline> quadPipeline;
		std::unique_ptr<Renderer::Graphics::RenderTarget> renderTarget;
		std::unique_ptr<Renderer::Graphics::RenderTarget> renderTarget1;

		Renderer::Graphics::RenderDevice* renderDevice;

		std::shared_ptr<Renderer::Graphics::Texture> quadTexture;
		std::shared_ptr<Renderer::Graphics::Texture> quadTexture1;

		std::shared_ptr<Renderer::Graphics::Models::Mesh> quadMesh;

		float vertices[8] = {
			 1.0f,  1.0f,  // top right
			 1.0f, -1.0f,  // bottom right
			-1.0f, -1.0f,  // bottom left
			-1.0f,  1.0f   // top left 
		};

		float texCoords[8] = {
			1.0f,  1.0f,   
			1.0f,  0.0f,   
			0.0f,  0.0f,   
			0.0f,  1.0f,   
		};

		unsigned int indices[6] = {
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

	};
}

