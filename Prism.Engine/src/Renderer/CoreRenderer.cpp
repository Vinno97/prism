#include "CoreRenderer.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "RenderFacade/RenderDevice.h"
#include "RenderFacade/VertexShader.h"
#include "RenderFacade/OGLRenderDevice.h"
#include "RenderFacade/OGLVertexShader.h"
#include "RenderFacade/OGLPipeline.h"

namespace Renderer {
	glm::mat4 trans = glm::mat4(1.0f);

	glm::mat4 view = glm::lookAt(
		glm::vec3(3.2f, 0.f, 1.2f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	);

	glm::mat4 proj = glm::perspective(glm::radians(70.0f), 1920.0f/1080.0f, 1.0f, 100.0f);
	auto t_start = std::chrono::high_resolution_clock::now();
	CoreRenderer::CoreRenderer()
	{
		renderDevice = new RenderFacade::OGLRenderDevice();
	}

	void CoreRenderer::init()
	{

		glEnable(GL_MULTISAMPLE);
		trans = glm::rotate(trans, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

		//Get vertex source
		const char* vertexShaderSource = { \
			"#version 330 core\n\
			layout (location = 0) in vec3 aPos; \
			uniform mat4 model;\
			uniform mat4 view;\
			uniform mat4 proj; \
			void main() { \
				gl_Position = proj * view * model * vec4(aPos.x, aPos.y, aPos.z, 1 ); \
			}"
		};
	

		const char* fragmentShaderSource =
		{
			"#version 330 core\n\
			uniform vec3 triangleColor;\
			out vec4 FragColor; \
			void main() { \
				FragColor = vec4(triangleColor, 1.0 ); \
			}"
		};


		vertexShader = renderDevice->createVertexShader(vertexShaderSource);
		fragmentShader = renderDevice->createFragmentShader(fragmentShaderSource);

		pipeline = renderDevice->createPipeline(vertexShader, fragmentShader);

		//Shaders have been uploaded to the GPU and no longer need to be held in memory
		delete vertexShader;
		delete fragmentShader;
		
		pipeline->createUniform("triangleColor");
		pipeline->createUniform("model");
		pipeline->createUniform("view");
		pipeline->createUniform("proj");

		//Initialize clear color
		glClearColor(1.f, 1.f, 1.f, 1.f);

		float vertices[] = {
		 0.5f,  0.5f, -2.0f,  // top right
		 0.5f, -0.5f, -2.0f,  // bottom right
		-0.5f, -0.5f, -2.0f,  // bottom left
		-0.5f,  0.5f, -2.0f   // top left 
		};
		unsigned int indices[] = {  
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		vertexBuffer = renderDevice->createVertexBuffer(sizeof(vertices), vertices);
		indexBuffer = renderDevice->createIndexBuffer(sizeof(indices), indices);
		indexBuffer->bind();

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		glEnable(GL_DEPTH_TEST);
		return;
	}


	void CoreRenderer::draw()
	{

		//Clear color buffer
		renderDevice->clearScreen();

		auto t_now = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

		pipeline->run();
		pipeline->setUniformVector("triangleColor", 0.0f, 0.0f, 1.0f);
		pipeline->setUniformMatrix4f("model", trans);
		pipeline->setUniformMatrix4f("view", view);
		pipeline->setUniformMatrix4f("proj", proj);

	    renderDevice->DrawTrianglesIndexed(0, 6);
		//glm::mat4 trans = glm::mat4(1.0f);
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(false);
		glDepthFunc(GL_EQUAL);

	    //trans = glm::translate(trans, glm::vec3(-0.5f, 2.f+(0.f+(time/5))*-1, -1.f));
	    pipeline->setUniformMatrix4f("model", trans);

		pipeline->setUniformVector("triangleColor", 0.f, 1.0f, 0.0f);
	    renderDevice->DrawTrianglesIndexed(0, 6);

		glDepthFunc(GL_LESS);
		glDepthMask(true);
		glDisable(GL_BLEND);

		pipeline->stop();
	}

	CoreRenderer::~CoreRenderer()
	{
		delete pipeline;
		delete vertexBuffer;
		delete renderDevice;
	}
}