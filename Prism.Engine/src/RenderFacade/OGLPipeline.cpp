#include <gl\glew.h>
#include <SDL2/SDL_opengl.h>
#include "RenderFacade/VertexShader.h"
#include "RenderFacade/FragmentShader.h"
#include "RenderFacade/OGLPipeline.h"
#include <iostream>

namespace RenderFacade {
	OGLPipeline::OGLPipeline(VertexShader vs, FragmentShader fs)
	{
		pipelineID = glCreateProgram();
		glAttachShader(pipelineID, vs.vertexID);
		glAttachShader(pipelineID, fs.fragmentID);
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
}
