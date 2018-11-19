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
#include "Util/FileSystem.h"

using namespace std;
using namespace Renderer;
using namespace Renderer::Graphics;
using namespace Renderer::Graphics::OpenGL;

namespace Renderer {
	ForwardRenderer::ForwardRenderer(int width, int height) : width{width}, height{height}
	{
		renderDevice = OGLRenderDevice::getRenderDevice();

		Util::FileSystem fileReader;
		string vertexSource = fileReader.readResourceFileIntoString("/shaders/simpleGeometry.vs");
		string fragmentSource = fileReader.readResourceFileIntoString("/shaders/simpleGeometry.fs");

		std::unique_ptr<VertexShader> vertexShader = renderDevice->createVertexShader(vertexSource.c_str());
		std::unique_ptr<FragmentShader> fragmentShader = renderDevice->createFragmentShader(fragmentSource.c_str());
		geometryPipeline = move(renderDevice->createPipeline(*vertexShader, *fragmentShader));

		geometryPipeline->createUniform("model");
		geometryPipeline->createUniform("view");
		geometryPipeline->createUniform("proj");

		geometryPipeline->createUniform("ambientLightColor");
		geometryPipeline->createUniform("ambientLightStrength");
		geometryPipeline->createUniform("objectColor");

		geometryPipeline->createUniform("sunPosition");
		geometryPipeline->createUniform("sunColor");
		geometryPipeline->createUniform("proj");

	    projection = glm::perspective(glm::radians(45.0f), (float) width/height, 0.5f, 100.0f);

		renderDevice->useDepthTest(true);
		renderDevice->setClearColour(0.7f, 0.7f, 0.7f, 1.f);
	}

	void ForwardRenderer::draw(const Camera& camera, const vector<Renderable>& renderables, Scene& scene)
	{
		mat4 model;
		mat4 view = camera.getCameraMatrix();
		renderDevice->clearScreen();
		geometryPipeline->run();

		for (auto& renderable : renderables) {

			model = renderable.getMatrix();
			geometryPipeline->setUniformMatrix4f("view", view);
			geometryPipeline->setUniformMatrix4f("proj", projection);
			geometryPipeline->setUniformMatrix4f("model", model);

			geometryPipeline->setUniformVector("ambientLightColor", scene.ambientLightColor.x, scene.ambientLightColor.y, scene.ambientLightColor.z);
			geometryPipeline->setUniformFloat("ambientLightStrength", scene.ambientLightStrength);

			geometryPipeline->setUniformVector("sunPosition", scene.sun.direction.x, scene.sun.direction.y, scene.sun.direction.z);
			geometryPipeline->setUniformVector("sunColor", scene.sun.color.x, scene.sun.color.y, scene.sun.color.z);

			geometryPipeline->setUniformVector("objectColor", renderable.color.x, renderable.color.y, renderable.color.z);

			renderable.model->mesh->vertexArrayObject->bind();
			if (renderable.model->mesh->isIndiced) {
				renderable.model->mesh->indexBuffer->bind();
				renderDevice->DrawTrianglesIndexed(0, renderable.model->mesh->indicesLength);
			}
			else {
				renderDevice->DrawTriangles(0, renderable.model->mesh->verticesLength);
			}
		}
		geometryPipeline->stop();
	}

	ForwardRenderer::~ForwardRenderer()
	{
		//std::cout << "end";
		//delete renderDevice;
	}
}
