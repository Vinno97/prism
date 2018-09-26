#pragma once
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "RenderAPI/OGLVertexArrayObject.h"
#include "RenderAPI/VertexBuffer.h"
#include "RenderAPI/OGLVertexBuffer.h"
#include <iostream> 

namespace RenderAPI {
	OGLVertexArrayObject::OGLVertexArrayObject() {
		glGenVertexArrays(1, &vaoID);
		glBindVertexArray(vaoID);
	}

	void OGLVertexArrayObject::addVertexBuffer(VertexBuffer* vertexBuffer, int index, long long size, int start, int stride)
	{
		bind();

		OGLVertexBuffer *oglVertexBuffer = reinterpret_cast<OGLVertexBuffer *>(vertexBuffer);
		oglVertexBuffer->bind();
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

		unbind();
	}

	void OGLVertexArrayObject::bind()
	{
		glBindVertexArray(vaoID);
	}

	void OGLVertexArrayObject::unbind()
	{
		glBindVertexArray(0);
	}

	OGLVertexArrayObject::~OGLVertexArrayObject()
	{
		glDeleteBuffers(1, &vaoID);
	}
};
