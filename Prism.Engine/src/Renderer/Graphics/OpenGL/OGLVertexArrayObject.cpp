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

			void OGLVertexArrayObject::addVertexBuffer(unique_ptr<VertexBuffer> vertexBuffer, int index, long long size, int start, int stride)
			{
				bind();
				
				VertexBuffer* buffer = vertexBuffer.get();
				OGLVertexBuffer *oglVertexBuffer = reinterpret_cast<OGLVertexBuffer *>(buffer);
				oglVertexBuffer->bind();
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, stride, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

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