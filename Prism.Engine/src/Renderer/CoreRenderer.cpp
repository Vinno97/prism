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


	glm::mat4 proj = glm::perspective(glm::radians(70.0f), 1920.0f/1080.0f, 1.0f, 10.0f);

	auto t_start = std::chrono::high_resolution_clock::now();
	CoreRenderer::CoreRenderer()
	{
		renderDevice = new RenderFacade::OGLRenderDevice();
	}

	void CoreRenderer::init()
	{

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
		
		pipeline->createUniform("triangleColor");
		pipeline->createUniform("model");
		pipeline->createUniform("view");
		pipeline->createUniform("proj");

		//Do Fragment
		//End new shaders

		//Success flag
		bool success = true;


		//Initialize clear color
		glClearColor(1.f, 1.f, 1.f, 1.f);

		float vertices[] = {
		 0.5f,  0.5f, -2.0f,  // top right
		 0.5f, -0.5f, -2.0f,  // bottom right
		-0.5f, -0.5f, -2.0f,  // bottom left
		-0.5f,  0.5f, -2.0f   // top left 
		};
		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		//Create VBO
		glGenBuffers(1, &gVBO);
		glBindBuffer(GL_ARRAY_BUFFER, gVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//Create IBO
		glGenBuffers(1, &gIBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//Enable vertex position

		//Set vertex data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		return;
	}


	void CoreRenderer::draw()
	{
		//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	//Render quad
		if (true)
		{
			auto t_now = std::chrono::high_resolution_clock::now();
			float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();


			pipeline->run();
			pipeline->setUniformVector("triangleColor", 1.0f, 0.0f, 0.0f);
			pipeline->setUniformMatrix4f("model", trans);
			pipeline->setUniformMatrix4f("view", view);
			pipeline->setUniformMatrix4f("proj", proj);
			//Set index data and render
			glm::mat4 trans = glm::mat4(1.0f);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
			trans = glm::translate(trans, glm::vec3(0.f, 2.f, -1.f));
			pipeline->setUniformMatrix4f("model", trans);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
			//Disable vertex position
			//glDisableVertexAttribArray(gVertexPos2DLocation);

			//Unbind program
			pipeline->stop();
		}
	}

	CoreRenderer::~CoreRenderer()
	{
	}
}