#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL2/SDL_opengl.h>
#include "RenderAPI/VertexShader.h"
#include "RenderAPI/FragmentShader.h"
#include "RenderAPI/OGLPipeline.h"
#include <iostream>

namespace RenderAPI {
	OGLPipeline::OGLPipeline(VertexShader* vs, FragmentShader* fs)
	{
		pipelineID = glCreateProgram();
		glAttachShader(pipelineID, vs->vertexID);
		glAttachShader(pipelineID, fs->fragmentID);
		glLinkProgram(pipelineID);
		GLint programSuccess = GL_TRUE;
		glGetProgramiv(pipelineID, GL_LINK_STATUS, &programSuccess);
		if (programSuccess != GL_TRUE)
		{
			printf("Error linking program %d!\n", pipelineID);
		}
	}

	OGLPipeline::~OGLPipeline()
	{
	}

	void OGLPipeline::run()
	{
		glUseProgram(pipelineID);
	}
	void OGLPipeline::stop()
	{
		glUseProgram(NULL);
	}
	bool OGLPipeline::createUniform(const char * name)
	{
		int uniColor = glGetUniformLocation(pipelineID, name);
		uniforms[name] = uniColor;
		return true;
	}
	bool OGLPipeline::setUniformMatrix4f(const char * name, glm::mat4 matrix)
	{
		int id = uniforms[name];
		glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(matrix));
		return true;
	}

	bool OGLPipeline::setUniformVector(const char * name, float x, float y, float z)
	{
		int id = uniforms[name];
		glUniform3f(id, x, y, z);
		return true;
	}
}
