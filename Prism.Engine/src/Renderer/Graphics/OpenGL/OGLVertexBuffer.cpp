#pragma once
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "Renderer/Graphics/OpenGL/OGLVertexBuffer.h"
#include <iostream> 

namespace Renderer {
	namespace Graphics {
		namespace OpenGL {
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
		}  // namespace OpenGL;
	}  // namespace Graphics
}  // namespace Renderer