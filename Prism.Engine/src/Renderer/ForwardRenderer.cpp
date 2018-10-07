#include "Renderer/ForwardRenderer.h"
#include <string>
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
#include "Util/FileReader.h"

using namespace std;
using namespace Renderer::Graphics;
using namespace Renderer::Graphics::OpenGL;

namespace Renderer {

	ForwardRenderer::ForwardRenderer(int width, int height)
	{
		renderDevice = OGLRenderDevice::getRenderDevice();

		Util::FileReader fileReader;
		string vertexSource = fileReader.readResourceFileIntoString("/shaders/simpleGeometry.vs");
		string fragmentSource = fileReader.readResourceFileIntoString("/shaders/simpleGeometry.fs");

		std::unique_ptr<VertexShader> vertexShader = renderDevice->createVertexShader(vertexSource.c_str());
		std::unique_ptr<FragmentShader> fragmentShader = renderDevice->createFragmentShader(fragmentSource.c_str());
		geometryPipeline = move(renderDevice->createPipeline(*vertexShader, *fragmentShader));

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
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(get<0>(renderable.position), get<1>(renderable.position), get<2>(renderable.position)));
			model = glm::scale(model, glm::vec3(get<0>(renderable.scale), get<1>(renderable.scale), get<2>(renderable.scale)));

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
	}
}
