#pragma once
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "RenderFacade/OGLIndexBuffer.h"
#include <iostream> 

namespace RenderFacade {
	OGLIndexBuffer::OGLIndexBuffer(long size, const void *data) {
		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void OGLIndexBuffer::bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	}

	OGLIndexBuffer::~OGLIndexBuffer()
	{
		glDeleteBuffers(1, &IBO);
	}
};
