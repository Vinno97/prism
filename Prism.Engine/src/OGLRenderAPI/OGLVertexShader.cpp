#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "RenderAPI/OGLVertexShader.h"
#include <iostream> 

namespace RenderAPI {
	OGLVertexShader::OGLVertexShader(const char* source) {

		//Create vertex shader
		vertexID = glCreateShader(GL_VERTEX_SHADER);
		
		//Set vertex source
		glShaderSource(vertexID, 1, &source, NULL);

		//Compile vertex source
		glCompileShader(vertexID);

		//Check vertex shader for errors
		GLint vShaderCompiled = GL_FALSE;
		glGetShaderiv(vertexID, GL_COMPILE_STATUS, &vShaderCompiled);
		if (vShaderCompiled != GL_TRUE)
		{
			printf("Unable to compile vertex shader %d!\n", vertexID);
		}
	}

	OGLVertexShader::~OGLVertexShader()
	{
	}
};
