#pragma once
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "Renderer/Graphics/OpenGL/OGLVertexArrayObject.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Renderer/Graphics/OpenGL/OGLVertexBuffer.h"
#include <iostream> 

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

				auto *oglVertexBuffer = reinterpret_cast<OGLVertexBuffer *>(vertexBuffer);
				oglVertexBuffer->bind();
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)nullptr);

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
		}  // namespace OpenGL;
	}  // namespace Graphics
}  // namespace Renderer