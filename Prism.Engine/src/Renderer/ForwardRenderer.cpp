#include <GL/glew.h>
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
#include "Renderer/Graphics/Pipeline.h"
#include "Renderer/Graphics/VertexArrayObject.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Renderer/Graphics/Loader/ModelLoader.h"
#include "Renderer/Graphics/Models/Model.h"
#include "Util/FileSystem.h"
#include <SDL2/SDL_opengl.h>

using namespace Renderer;
using namespace Renderer::Graphics;
using namespace Renderer::Graphics::OpenGL;

using namespace Renderer::Graphics::Models;

namespace Renderer {
	ForwardRenderer::ForwardRenderer(int width, int height) : width{width}, height{height}
	{
		renderDevice = OGLRenderDevice::getRenderDevice();

		positionBuffer = renderDevice->createTexture();
		normalBuffer = renderDevice->createTexture();
		albedoBuffer = renderDevice->createTexture();

		renderTarget = renderDevice->createRenderTarget(true , positionBuffer);

		renderTarget->addBuffer(positionBuffer);
		renderTarget->addBuffer(normalBuffer);
		renderTarget->addBuffer(albedoBuffer);

		loadPipelines();
		createTargetQuad();

	    projection = glm::perspective(glm::radians(45.0f), (float) width/height, 0.5f, 100.0f);

		renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
	}

	void ForwardRenderer::draw(const Camera& camera, const std::vector<Renderable>& renderables, const Scene& scene)
	{
		glm::mat4 model;
		const glm::mat4 view = camera.getCameraMatrix();
		renderDevice->useDepthTest(true);
		renderDevice->clearScreen();
			
		renderTarget->bind();
		renderDevice->clearScreen();
		geometryPipeline->run();


		for (const auto& renderable : renderables) {
			model = renderable.getMatrix();

			geometryPipeline->setUniformMatrix4f("view", view);
			geometryPipeline->setUniformMatrix4f("proj", projection);
			geometryPipeline->setUniformMatrix4f("model", model);

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

		renderTarget->unbind();
		geometryPipeline->stop();
	
		quadPipeline->run();
		
		quadPipeline->setUniformVector("ambientLightColor", scene.ambientLightColor.x, scene.ambientLightColor.y, scene.ambientLightColor.z);
		quadPipeline->setUniformFloat("ambientLightStrength", scene.ambientLightStrength);
		quadPipeline->setUniformVector("sunPosition", scene.sun.direction.x, scene.sun.direction.y, scene.sun.direction.z);
		quadPipeline->setUniformVector("sunColor", scene.sun.color.x, scene.sun.color.y, scene.sun.color.z);

		positionBuffer->bind(textures[0]);
		normalBuffer->bind(textures[1]);
		albedoBuffer->bind(textures[2]);

		quadMesh->vertexArrayObject->bind();
		quadMesh->indexBuffer->bind();
		glViewport(0, 0, 1920 / 2, 1080 / 2); 
		renderDevice->DrawTrianglesIndexed(0, quadMesh->indicesLength);

		quadMesh->vertexArrayObject->unbind();

		quadPipeline->stop();
		renderDevice->useDepthTest(false);
	}
	void ForwardRenderer::createTargetQuad()
	{
		const float* verticesArray = vertices;
		const float* textsArray = texCoords;
		const unsigned int* indicesArray = indices;

		auto verticesSize = 8 * sizeof(float);

		std::unique_ptr<VertexBuffer> vertexBuffer = renderDevice->createVertexBuffer(verticesSize, vertices);
		std::unique_ptr<VertexBuffer> texBuffer = renderDevice->createVertexBuffer(verticesSize, texCoords);

		std::unique_ptr<IndexBuffer> indexBuffer = renderDevice->createIndexBuffer(6 * sizeof(unsigned int), indices);

		std::unique_ptr<VertexArrayObject> vertexArrayObject = renderDevice->createVertexArrayobject();
		vertexArrayObject->addVertexBuffer(vertexBuffer.get(), 0, 2 * sizeof(float), 0, 2);
		vertexArrayObject->addVertexBuffer(texBuffer.get(), 1, 2 * sizeof(float), 0, 2);

		quadMesh = std::make_shared<Renderer::Graphics::Models::Mesh>(move(vertexArrayObject), move(indexBuffer));
		quadMesh->isIndiced = true;
		quadMesh->indicesLength = 6;

	}
	void ForwardRenderer::loadPipelines()
	{
		//Setup geometry shaders
		Util::FileSystem fileReader;
		std::string vertexSource = fileReader.readResourceFileIntoString("/shaders/simpleGeometry.vs");
		std::string fragmentSource = fileReader.readResourceFileIntoString("/shaders/simpleGeometry.fs");
		std::unique_ptr<VertexShader> vertexShader = renderDevice->createVertexShader(vertexSource.c_str());
		std::unique_ptr<FragmentShader> fragmentShader = renderDevice->createFragmentShader(fragmentSource.c_str());
		geometryPipeline = move(renderDevice->createPipeline(*vertexShader, *fragmentShader));

		geometryPipeline->createUniform("objectColor");
		geometryPipeline->createUniform("model");
		geometryPipeline->createUniform("view");
		geometryPipeline->createUniform("proj");

		//Setup quad shaders
		vertexSource = fileReader.readResourceFileIntoString("/shaders/quadShader.vs");
		fragmentSource = fileReader.readResourceFileIntoString("/shaders/quadShader.fs");

		vertexShader = renderDevice->createVertexShader(vertexSource.c_str());
		fragmentShader = renderDevice->createFragmentShader(fragmentSource.c_str());

		quadPipeline = move(renderDevice->createPipeline(*vertexShader, *fragmentShader));

		quadPipeline->createUniform("ambientLightColor");
		quadPipeline->createUniform("ambientLightStrength");
					
		quadPipeline->createUniform("sunPosition");
		quadPipeline->createUniform("sunColor");
	}
}
