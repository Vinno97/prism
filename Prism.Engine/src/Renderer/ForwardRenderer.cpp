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

	    projection = glm::perspective(glm::radians(45.0f), (float) width/height, 1.f, 100.0f);

		renderDevice->useDepthTest(true);
		renderDevice->setClearColour(0.7f, 0.7f, 0.7f, 1.f);
	}

	void ForwardRenderer::draw(Camera* camera, vector<Renderable> renderables)
	{
		mat4 model;
		mat4 view = camera->getCameraMatrix();
		renderDevice->clearScreen();
		geometryPipeline->run();

		for (auto renderable : renderables) {

			model = renderable.getMatrix();
			geometryPipeline->setUniformMatrix4f("view", view);
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
