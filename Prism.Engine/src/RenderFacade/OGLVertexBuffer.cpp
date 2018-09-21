#pragma once
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "RenderFacade/OGLVertexBuffer.h"
#include <iostream> 

namespace RenderFacade {
	OGLVertexBuffer::OGLVertexBuffer(long size, const void *data) {
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); // always assuming static, for now
	}

	void OGLVertexBuffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
	}

	OGLVertexBuffer::~OGLVertexBuffer()
	{
		glDeleteBuffers(1, &VBO);
	}
};
