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

		positionBuffer = renderDevice->createTexture(false);
		normalBuffer = renderDevice->createTexture(false);
		albedoBuffer = renderDevice->createTexture(false);
		depthBuffer = renderDevice->createTexture(true);

		renderTarget = renderDevice->createRenderTarget(true);

		renderTarget->addBuffer(positionBuffer);
		renderTarget->addBuffer(normalBuffer);
		renderTarget->addBuffer(albedoBuffer);
		renderTarget->setDepthBuffer(depthBuffer);

		shadowDepthBuffer = renderDevice->createTexture(true);
		shadowDepthTarget = renderDevice->createRenderTarget(true); 
		shadowDepthTarget->setDepthBuffer(shadowDepthBuffer);

		loadPipelines();
		createTargetQuad();

	    projection = glm::perspective(glm::radians(45.0f), (float) width/height, 0.5f, 100.f);
	    shadowProjection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.f, 7.5f);

		renderDevice->setClearColour(1.f, 1.f, 1.f, 1.f);
		shadowCamera.position = glm::vec3{ -45.f, 1.0f, -15 };
		shadowCamera.rotation = glm::vec3{ -40.f, 0.f, 0.f };
	}

	float i = 0;

	void ForwardRenderer::draw(const Camera& camera, const std::vector<Renderable>& renderables, const Scene& scene, const std::vector<PointLight>& pointLights, Math::Vector3f position)
	{

		i += 0.01;
		glm::mat4 model;
		const glm::mat4 view = camera.getCameraMatrix();
		shadowCamera.position = glm::vec3(position.x, position.y, position.z);
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

		//Render shadowmap

		shadowDepthTarget->bind();
		shadowPipeline->run();
		renderDevice->clearScreen();
		auto shadowView = shadowCamera.getCameraMatrix();
		glCullFace(GL_FRONT);

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
		glCullFace(GL_BACK);
		shadowPipeline->stop();
		shadowDepthTarget->unbind();

		//End render shadowmap

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
		
	//	int i = 0;
	//	for (auto const& light : pointLights) {
	//		std::string index = "gPointLights[" + std::to_string(i) + "]";
	//		quadPipeline->setUniformVector(index.append(".Color").c_str(), 1.0f, 0.0f, 0.0f);
	//		quadPipeline->setUniformVector(index.append(".Position").c_str(), 1.0f, 0.0f, 0.0f);
	//		quadPipeline->setUniformFloat(index.append(".AmbientIntensity").c_str(), light.ambientIntensity);
	//		quadPipeline->setUniformFloat(index.append(".DiffuseIntensity").c_str(), light.ambientIntensity);
	//		quadPipeline->setUniformFloat(index.append(".Constant").c_str(), light.constant);
	//		quadPipeline->setUniformFloat(index.append(".Linear").c_str(), light.linear);
	//		quadPipeline->setUniformFloat(index.append(".Exp").c_str(), light.exp);
	//	}

		PointLight pl{ Math::Vector3f{-41.f, 3, -15.f}, Math::Vector3f{1.f, 0, 0.f} };

		pl.constant = 1.0f;
		pl.linear = 0.7f;
		pl.exp = 1.8f;

	//quadPipeline->setUniformVector("gPointLight.Color", pl.color.x, pl.color.y, pl.color.z);
	//quadPipeline->setUniformVector("gPointLight.Position", pl.position.x, pl.position.y, pl.position.z);
	//
	//quadPipeline->setUniformFloat("gPointLight.AmbientIntensity", pl.ambientIntensity);
	//quadPipeline->setUniformFloat("gPointLight.DiffuseIntensity", pl.diffuseIntensity);
	//quadPipeline->setUniformFloat("gPointLight.Constant", pl.constant);
	//quadPipeline->setUniformFloat("gPointLight.Linear", pl.linear);
	//quadPipeline->setUniformFloat("gPointLight.Exp", pl.exp);
		
		positionBuffer->bind(textures[0]);
		normalBuffer->bind(textures[1]);
		albedoBuffer->bind(textures[2]);
		depthBuffer->bind(textures[3]);
		shadowDepthBuffer->bind(textures[4]);

		quadMesh->vertexArrayObject->bind();
		quadMesh->indexBuffer->bind();
		glViewport(0, 0, 1920, 1080); 
		renderDevice->DrawTrianglesIndexed(0, quadMesh->indicesLength);

		quadMesh->vertexArrayObject->unbind();

		quadPipeline->stop();
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
		vertexArrayObject->addVertexBuffer(move(vertexBuffer), 0, 2 * sizeof(float), 0, 2);
		vertexArrayObject->addVertexBuffer(move(texBuffer), 1, 2 * sizeof(float), 0, 2);

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

		//quadPipeline->createUniform("gPointLight.Color");
		//quadPipeline->createUniform("gPointLight.Position");
		//quadPipeline->createUniform("gPointLight.AmbientIntensity");
		//quadPipeline->createUniform("gPointLight.DiffuseIntensity");
		//quadPipeline->createUniform("gPointLight.Constant");
		//quadPipeline->createUniform("gPointLight.Linear");
		//quadPipeline->createUniform("gPointLight.Exp");

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

		geometryPipeline->createUniform("model");
		shadowPipeline->createUniform("view");
		shadowPipeline->createUniform("proj");
	}
}
