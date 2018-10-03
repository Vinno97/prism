#include "Renderer/TestRenderer.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <chrono>
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
using namespace Renderer::Graphics::Loader;
using namespace Renderer::Graphics::Models;

namespace Renderer {
	glm::mat4 trans = glm::mat4(1.0f);

	glm::mat4 view = glm::lookAt(
		glm::vec3(5.2f, 0.f, 1.2f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	);

	VertexArrayObject* vertexArray1;

	glm::mat4 proj = glm::perspective(glm::radians(70.0f), 1920.0f/1080.0f, 1.0f, 100.0f);
	auto t_start = std::chrono::high_resolution_clock::now();

	TestRenderer::TestRenderer()
	{
		renderDevice = new OGLRenderDevice();
	}

	void TestRenderer::init()
	{


		//Matrix for object in worldspace
		trans = glm::rotate(trans, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));


		//Make and compile shaders
		const char* vertexShaderSource = { \
			"#version 330 core\n\
			layout (location = 0) in vec3 aPos; \
			layout (location = 1) in vec3 colour; \
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
		ModelLoader* modelLoader = new ModelLoader(renderDevice);
		string path = "C:/Users/Daan/Prism/prism/x64/Debug/bunny.obj";
		model = modelLoader->loadModel(path);

		vertexShader = renderDevice->createVertexShader(vertexShaderSource);
		fragmentShader = renderDevice->createFragmentShader(fragmentShaderSource);

		//Link shaders into program/pipeline
		pipeline = renderDevice->createPipeline(vertexShader, fragmentShader);

		//Shaders have been uploaded to the GPU and no longer need to be held in memory
		delete vertexShader;
		delete fragmentShader;
	
		//Before we can use uniforms in the shader we first need to 'find' them
		pipeline->createUniform("model");
		pipeline->createUniform("view");
		pipeline->createUniform("proj");

		//Initialize clear color
		renderDevice->setClearColour(0.7f, 0.7f, 0.7f, 1.f);

		//Square shape
		float vertices[] = {
		 0.5f,  0.5f, -2.0f,  // top right
		 0.5f, -0.5f, -2.0f,  // bottom right
		-0.5f, -0.5f, -2.0f,  // bottom left
		-0.5f,  0.5f, -2.0f   // top left 
		};

		//Colours for square
	    float colours[] = {
		 0.8f,  0.2f, 0.5f,  
		 0.5f,  0.5f, 0.5f, 
		 0.5f,  0.1f, 0.9f, 
		 0.9f,  0.5f, 0.2f,
		};

		unsigned int indices[] = {  
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};
		//Create VAO
		vertexArray1 = renderDevice->createVertexArrayobject();

		//Vertex buffer with vertices
		vertexBuffer = renderDevice->createVertexBuffer(sizeof(vertices), vertices);

		//Another buffer for the colours
		VertexBuffer* colourBuffer = renderDevice->createVertexBuffer(sizeof(colours), colours);

		//Indices buffer
		indexBuffer = renderDevice->createIndexBuffer(sizeof(indices), indices);
		indexBuffer->bind();

		//Add vertex and colour buffer to the vao
		vertexArray1->addVertexBuffer(vertexBuffer, 0, 3 * sizeof(GLfloat), 0, 3);
		vertexArray1->addVertexBuffer(colourBuffer, 1, 3 * sizeof(GLfloat), 0, 3);

		vertexArray1->unbind();
		
		renderDevice->useDepthTest(true);
		trans = glm::scale(trans, glm::vec3(20.f, 20.f, 20.f));
		return;
	}


	void TestRenderer::draw()
	{
		//Enable VAO
		//vertexArray1->bind();
		model->mesh->vertexArrayObject->bind();
		model->mesh->indexBuffer->bind();
		//Clear color buffer
		renderDevice->clearScreen();

		auto t_now = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

		pipeline->run();


		pipeline->setUniformMatrix4f("model", trans);
		pipeline->setUniformMatrix4f("view", view);
		pipeline->setUniformMatrix4f("proj", proj);

	    renderDevice->DrawTrianglesIndexed(0, model->mesh->indicesLength);

		pipeline->stop();
	}

	TestRenderer::~TestRenderer()
	{
		delete pipeline;
		delete vertexBuffer;
		delete renderDevice;
	}
}