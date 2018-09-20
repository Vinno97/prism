#pragma once
#include <gl\glew.h>
#include <SDL2/SDL_opengl.h>
#include "RenderFacade/OGLVertexShader.h"
#include <iostream> 
namespace RenderFacade {
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

	bool OGLVertexShader::createUniform(const char* name) {
		return true;
	}

	OGLVertexShader::~OGLVertexShader()
	{
	}
};
