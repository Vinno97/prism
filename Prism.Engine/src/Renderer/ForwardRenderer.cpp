#include "Renderer/ForwardRenderer.h"

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
using namespace Renderer::Graphics::OpenGL;

namespace Renderer {

	
	ForwardRenderer::ForwardRenderer(int width, int height)
	{

		renderDevice = OGLRenderDevice::getRenderDevice();

		const char* vertexShaderSource = { \
			"#version 330 core\n\
			layout (location = 0) in vec3 aPos; \
			out vec4 pass_colour;\
			uniform mat4 model;\
			uniform mat4 view;\
			uniform mat4 proj; \
			void main() { \
				gl_Position = proj * view * model * vec4(aPos.x, aPos.y, aPos.z, 1 ); \
				pass_colour = view * model * vec4(aPos.x, aPos.y, aPos.z, 1); \
			}"
		};
	
		const char* fragmentShaderSource =
		{
			"#version 330 core\n\
			in vec4 pass_colour; \
			out vec4 FragColor; \
			void main() { \
				FragColor = pass_colour*-1; \
			}"
		};

		VertexShader* vertexShader = renderDevice->createVertexShader(vertexShaderSource);
		FragmentShader* fragmentShader = renderDevice->createFragmentShader(fragmentShaderSource);
		geometryPipeline = renderDevice->createPipeline(vertexShader, fragmentShader);

		delete vertexShader;
		delete fragmentShader;

		geometryPipeline->createUniform("model");
		geometryPipeline->createUniform("view");
		geometryPipeline->createUniform("proj");

		camera = glm::lookAt(
			glm::vec3(0.0f, 0.0f, 3.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);

	    projection = glm::perspective(glm::radians(70.0f), 1920.0f/1080.0f, 1.f, 100.0f);

		renderDevice->useDepthTest(true);
		renderDevice->setClearColour(0.7f, 0.7f, 0.7f, 1.f);
	}

	void ForwardRenderer::draw(vector<Renderable> renderables)
	{
		renderDevice->clearScreen();
		geometryPipeline->run();

		for (auto renderable : renderables) {
			auto position = glm::vec3(get<0>(renderable.position), get<1>(renderable.position), get<2>(renderable.position));
			model = glm::mat4(1.0f);
			model = glm::translate(model, position);
			//camera = glm::rotate(camera, glm::radians(0.1f), glm::vec3(0.f, 1.f, 0.f));

			geometryPipeline->setUniformMatrix4f("view", camera);
			geometryPipeline->setUniformMatrix4f("proj", projection);
			geometryPipeline->setUniformMatrix4f("model", model);

			renderable.model->mesh->vertexArrayObject->bind();
			renderable.model->mesh->indexBuffer->bind();
			renderDevice->DrawTrianglesIndexed(0, renderable.model->mesh->indicesLength);
		}
		geometryPipeline->stop();
	}

	ForwardRenderer::~ForwardRenderer()
	{
		delete geometryPipeline;
	}
}
