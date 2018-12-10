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
#include "Math/Vector3f.h"
#include <SDL2/SDL_opengl.h>

using namespace Math;
using namespace Renderer;
using namespace Renderer::Graphics;
using namespace Renderer::Graphics::OpenGL;
using namespace Renderer::Graphics::Models;

namespace Renderer {
	ForwardRenderer::ForwardRenderer(int width, int height) : width{width}, height{height}
	{
		renderDevice = OGLRenderDevice::getRenderDevice();

		positionBuffer = renderDevice->createTexture(false, width, height);
		normalBuffer = renderDevice->createTexture(false, width, height);
		albedoBuffer = renderDevice->createTexture(false, width, height);
		depthBuffer = renderDevice->createTexture(true, width, height);

		renderTarget = renderDevice->createRenderTarget(true);

		renderTarget->addBuffer(positionBuffer);
		renderTarget->addBuffer(normalBuffer);
		renderTarget->addBuffer(albedoBuffer);
		renderTarget->setDepthBuffer(depthBuffer);

		shadowDepthTarget = renderDevice->createRenderTarget(true); 
		shadowDepthBuffer = renderDevice->createTexture(true, width ,height);
		shadowDepthTarget->setDepthBuffer(shadowDepthBuffer);

		loadPipelines();
		createTargetQuad();

	    projection = glm::perspective(glm::radians(45.0f), (float) width/height, 0.5f, 100.f);
		shadowProjection = glm::ortho(-5.f, 5.f, -5.f, 5.f, 0.f, 30.f);

		renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
		shadowCamera.position = glm::vec3{ -55.f, 11.0f, -25 };
	}

	float i = 0;

	void ForwardRenderer::draw(const Camera& camera, const std::vector<Renderable>& renderables, const Scene& scene, std::vector<PointLight>& pointLights, Math::Vector3f position)
	{

		i += 0.01;
		glm::mat4 model;
		const glm::mat4 view = camera.getCameraMatrix();
		shadowCamera.position = camera.position;
		shadowCamera.position.x -= 4;
		shadowCamera.position.y -= 1;
		shadowCamera.target = camera.target;

		glViewport(0, 0, width, height);
		//Do GBuffer pass
		renderDevice->clearScreen();
			
		renderTarget->bind();
		renderDevice->useDepthTest(true);
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
		//End GBuffer pass

		//Shadow depth map render
		shadowDepthTarget->bind();
		renderDevice->useDepthTest(true);
		renderDevice->clearScreen();
		shadowPipeline->run();

		auto shadowView = shadowCamera.getCameraMatrix();

		for (const auto& renderable : renderables) {
			model = renderable.getMatrix();

			shadowPipeline->setUniformMatrix4f("view", shadowView);
			shadowPipeline->setUniformMatrix4f("proj", shadowProjection);
			shadowPipeline->setUniformMatrix4f("model", model);

			renderable.model->mesh->vertexArrayObject->bind();
			if (renderable.model->mesh->isIndiced) {
				renderable.model->mesh->indexBuffer->bind();
				renderDevice->DrawTrianglesIndexed(0, renderable.model->mesh->indicesLength);
			}
			else {
				renderDevice->DrawTriangles(0, renderable.model->mesh->verticesLength);
			}
		}

		shadowDepthTarget->unbind();
		shadowPipeline->stop();
		//End shadow depth map render

		//Do lighting pass
		renderDevice->useDepthTest(false);
		quadPipeline->run();
		
		quadPipeline->setUniformVector("gDirectionalLight.Color", scene.ambientLightColor.x, scene.ambientLightColor.y, scene.ambientLightColor.z);
		quadPipeline->setUniformVector("gDirectionalLight.Direction", scene.sun.direction.x, scene.sun.direction.y, scene.sun.direction.z);

		quadPipeline->setUniformFloat("gDirectionalLight.AmbientIntensity", 0.6f);
		quadPipeline->setUniformFloat("gDirectionalLight.DiffuseIntensity", 0.5f);

		quadPipeline->setUniformMatrix4f("shadowView", shadowView);
		quadPipeline->setUniformMatrix4f("view", view);
		quadPipeline->setUniformMatrix4f("proj", projection);
		quadPipeline->setUniformMatrix4f("shadowProj", shadowProjection);

		quadPipeline->setUniformFloat("numPointLights", pointLights.size());

		int index = 0;
		for (auto const& light : pointLights) {
			std::string location = "gPointLights";
			location.append("[").append(std::to_string(index).append("]"));

			auto color = location + ".Color";
			quadPipeline->setUniformVector(color.c_str(), light.color.x, light.color.y, light.color.z);

			color = location + ".Position";
			quadPipeline->setUniformVector(color.c_str(), light.position.x, light.position.y, light.position.z);

			color = location + ".AmbientIntensity";
			quadPipeline->setUniformFloat(color.c_str(), light.ambientIntensity);

			color = location + ".DiffuseIntensity";
			quadPipeline->setUniformFloat(color.c_str(), light.diffuseIntensity);

			color = location + ".Constant";
			quadPipeline->setUniformFloat(color.c_str(), light.constant);

			color = location + ".Linear";
			quadPipeline->setUniformFloat(color.c_str(), light.linear);

			color = location + ".Exp";
			quadPipeline->setUniformFloat(color.c_str(), light.exp);


			index++;
		}
		
		positionBuffer->bind(textures[0]);
		normalBuffer->bind(textures[1]);
		albedoBuffer->bind(textures[2]);
		depthBuffer->bind(textures[3]);
		shadowDepthBuffer->bind(textures[4]);

		quadMesh->vertexArrayObject->bind();
		quadMesh->indexBuffer->bind();
		renderDevice->DrawTrianglesIndexed(0, quadMesh->indicesLength);

		quadMesh->vertexArrayObject->unbind();

		quadPipeline->stop();
		//End lighting pass
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
					
		quadPipeline->createUniform("gDirectionalLight.Direction");
		quadPipeline->createUniform("gDirectionalLight.Color");
		quadPipeline->createUniform("gDirectionalLight.AmbientIntensity");
		quadPipeline->createUniform("gDirectionalLight.DiffuseIntensity");

		for (int i = 0; i < 100; i++) {
			std::string location = "gPointLights";
			location.append("[").append(std::to_string(i).append("]"));

			auto color = location + ".Color";
			quadPipeline->createUniform(color.c_str());

			color = location + ".Position";
			quadPipeline->createUniform(color.c_str());

			color = location + ".AmbientIntensity";
			quadPipeline->createUniform(color.c_str());

			color = location + ".DiffuseIntensity";
			quadPipeline->createUniform(color.c_str());

			color = location + ".Constant";
			quadPipeline->createUniform(color.c_str());

			color = location + ".Linear";
			quadPipeline->createUniform(color.c_str());

			color = location + ".Exp";
			quadPipeline->createUniform(color.c_str());
		}


		quadPipeline->createUniform("numPointLights");

		quadPipeline->createUniform("view");
		quadPipeline->createUniform("shadowView");
		quadPipeline->createUniform("shadowProj");
		quadPipeline->createUniform("proj");


		//setup shadow shader

		vertexSource = fileReader.readResourceFileIntoString("/shaders/shadowShader.vs");
		fragmentSource = fileReader.readResourceFileIntoString("/shaders/shadowShader.fs");

		vertexShader = renderDevice->createVertexShader(vertexSource.c_str());
		fragmentShader = renderDevice->createFragmentShader(fragmentSource.c_str());

		shadowPipeline = move(renderDevice->createPipeline(*vertexShader, *fragmentShader));

		shadowPipeline->createUniform("model");
		shadowPipeline->createUniform("view");
		shadowPipeline->createUniform("proj");
	}
}
