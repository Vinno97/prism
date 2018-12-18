#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <memory>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Renderable.h"
#include "Renderer/Camera.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/RenderTarget.h"
#include "Renderer/Graphics/Texture.h"
#include "Renderer/Graphics/Models/Mesh.h"
#include "Renderer/PointLight.h"
#include "Renderer/Scene.h"
#include "Math/Vector3f.h"
#include "../../lib/include/glm/mat4x4.hpp"


namespace Renderer {
	class ForwardRenderer
	{
	public:
		ForwardRenderer(int width, int height);
		
		/// <summary>
		/// Draws the list of renderables from the viewpoint of a given camera
		/// </summary>
		void draw(const Camera& camera, const std::vector<Renderable>& renderables, const Renderer::Scene& scene, std::vector<PointLight>& pointLights, Math::Vector3f position, const int width, const int height);

		int width;
		int height;
		void loadPipelines();
	private: 
		void createTargetQuad();

		Camera shadowCamera;

		glm::mat4 projection = glm::mat4(1.0f);
		glm::mat4 shadowProjection = glm::mat4(1.0f);
		std::unique_ptr<Renderer::Graphics::Pipeline> geometryPipeline;
		std::unique_ptr<Renderer::Graphics::Pipeline> shadowPipeline;
		std::unique_ptr<Renderer::Graphics::RenderTarget> renderTarget;
		std::unique_ptr<Renderer::Graphics::Pipeline> quadPipeline;
		std::shared_ptr<Renderer::Graphics::Models::Mesh> quadMesh;
		Renderer::Graphics::RenderDevice* renderDevice;

		std::unique_ptr<Renderer::Graphics::RenderTarget> shadowDepthTarget;
		std::shared_ptr<Renderer::Graphics::Texture> shadowDepthBuffer;
		std::shared_ptr<Renderer::Graphics::Texture> shadowTest;

		std::shared_ptr<Renderer::Graphics::Texture> positionBuffer;
		std::shared_ptr<Renderer::Graphics::Texture> normalBuffer;
		std::shared_ptr<Renderer::Graphics::Texture> albedoBuffer;
		std::shared_ptr<Renderer::Graphics::Texture> depthBuffer;

		const float vertices[8] = {
			 1.0f,  1.0f,  // top right
			 1.0f, -1.0f,  // bottom right
			-1.0f, -1.0f,  // bottom left
			-1.0f,  1.0f   // top left 
		};

		const float texCoords[8] = {
			1.0f,  1.0f,   
			1.0f,  0.0f,   
			0.0f,  0.0f,   
			0.0f,  1.0f,   
		};

		const unsigned int indices[6] = {
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		glm::mat4 biasMatrix = glm::mat4(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
		);

	};
}

