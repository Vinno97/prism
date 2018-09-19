#include "CoreRenderer.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "RenderFacade/RenderDevice.h"
#include "RenderFacade/VertexShader.h"
#include "RenderFacade/OGLRenderDevice.h"
#include "RenderFacade/OGLVertexShader.h"

namespace Renderer {

	CoreRenderer::CoreRenderer()
	{
		renderDevice = RenderFacade::OGLRenderDevice();
	}

	void CoreRenderer::init()
	{

		//New shaders

		//Get vertex source
		const char* vertexShaderSource =
		{
			"#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
		};

		//vertexShader = renderDevice.createVertexShader(vertexShaderSource);
		//End new shaders

		//Success flag
		bool success = true;

		//Generate program
		gProgramID = glCreateProgram();

		//Create vertex shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		
		//Set vertex source
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

		//Compile vertex source
		glCompileShader(vertexShader);

		//Check vertex shader for errors
		GLint vShaderCompiled = GL_FALSE;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
		if (vShaderCompiled != GL_TRUE)
		{
			printf("Unable to compile vertex shader %d!\n", vertexShader);
			success = false;
		}
		else
		{
			//Attach vertex shader to program
			glAttachShader(gProgramID, vertexShader);


			//Create fragment shader
			GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			//Get fragment source
			const GLchar* fragmentShaderSource[] =
			{
				"#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
			};

			//Set fragment source
			glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);

			//Compile fragment source
			glCompileShader(fragmentShader);

			//Check fragment shader for errors
			GLint fShaderCompiled = GL_FALSE;
			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
			if (fShaderCompiled != GL_TRUE)
			{
				printf("Unable to compile fragment shader %d!\n", fragmentShader);
				success = false;
			}
			else
			{
				//Attach fragment shader to program
				glAttachShader(gProgramID, fragmentShader);


				//Link program
				glLinkProgram(gProgramID);

				//Check for errors
				GLint programSuccess = GL_TRUE;
				glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
				if (programSuccess != GL_TRUE)
				{
					printf("Error linking program %d!\n", gProgramID);
					success = false;
				}
				else
				{
					//Get vertex attribute location
					gVertexPos2DLocation = glGetAttribLocation(gProgramID, "LVertexPos2D");
					if (gVertexPos2DLocation == -1)
					{
						printf("LVertexPos2D is not a valid glsl program variable!\n");
						success = false;
					}
					else
					{
						//Initialize clear color
						glClearColor(0.f, 0.f, 0.f, 1.f);

						//VBO data
						GLfloat vertexData[] =
						{
							-0.5f, -0.5f,
							0.5f, -0.5f,
							0.5f,  0.5f,
							-0.5f,  0.5f
						};

						//IBO data
						GLuint indexData[] = { 0, 1, 2, 3 };

						//Create VBO
						glGenBuffers(1, &gVBO);
						glBindBuffer(GL_ARRAY_BUFFER, gVBO);
						glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

						//Create IBO
						glGenBuffers(1, &gIBO);
						glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
						glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
					}
				}
			}
		}

		return;
	}


	void CoreRenderer::draw()
	{
		//Clear color buffer
		glClear(GL_COLOR_BUFFER_BIT);


		//Render quad
		if (true)
		{
			//Bind program
			glUseProgram(gProgramID);

			//Enable vertex position
			glEnableVertexAttribArray(gVertexPos2DLocation);

			//Set vertex data
			glBindBuffer(GL_ARRAY_BUFFER, gVBO);
			glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

			//Set index data and render
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
			glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

			//Disable vertex position
			glDisableVertexAttribArray(gVertexPos2DLocation);

			//Unbind program
			glUseProgram(NULL);
		}
	}

	CoreRenderer::~CoreRenderer()
	{
	}
}