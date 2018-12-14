#pragma once
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "Renderer/Graphics/OpenGL/OGLVertexArrayObject.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Renderer/Graphics/OpenGL/OGLVertexBuffer.h"
#include <iostream> 
#include <memory>

using namespace std;

namespace Renderer {
	namespace Graphics {
		namespace OpenGL {
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
				glVertexAttribPointer(index, stride, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), 0);
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
	}
}