#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "Renderer/Graphics/OpenGL/OGLVertexBuffer.h"
#include <iostream>

namespace Renderer
{
	namespace Graphics
	{
		namespace OpenGL
		{
			OGLVertexBuffer::OGLVertexBuffer(long size, const void* data)
			{
				glGenBuffers(1, &VBO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); // always assuming static, for now
			}

			OGLVertexBuffer::OGLVertexBuffer()
			{
				glGenBuffers(1, &VBO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
			}

			void OGLVertexBuffer::bind()
			{
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
			}

			void OGLVertexBuffer::unbind()
			{
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			void OGLVertexBuffer::rebuffer(long size, const void* data)
			{
				glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
			}

			OGLVertexBuffer::~OGLVertexBuffer()
			{
				glDeleteBuffers(1, &VBO);
			}
		};
	}
}
