#pragma once;
#include <gl/glew.h>
#include <SDL2/SDL_opengl.h>
#include <iostream> 
#include "RenderFacade/OGLFragmentShader.h"

namespace RenderFacade {

	OGLFragmentShader::OGLFragmentShader(const char* source)
	{
		fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(fragmentID, 1, &source, NULL);

		glCompileShader(fragmentID);

		GLint fShaderCompiled = GL_FALSE;
		glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &fShaderCompiled);
		if (fShaderCompiled != GL_TRUE)
		{
			printf("Unable to compile fragment shader %d!\n", fragmentID);
		}
	}

	bool OGLFragmentShader::createUniform(const char* name) {
		int uniColor = glGetUniformLocation(fragmentID, name);
		uniforms[name] = uniColor;
		return true;
	}


	bool OGLFragmentShader::setUniformVector(const char* name, float x, float y, float z) {
		int id = uniforms[name];
		glUniform3f(id, x, y, z);
		return true;
	}

	//QQQ Delete shader
	OGLFragmentShader::~OGLFragmentShader()
	{
	}
}
