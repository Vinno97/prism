#pragma once
#include "Renderer/Graphics/VertexBuffer.h"
#include <SDL2/SDL_opengl.h>

namespace Renderer {
	namespace Graphics {
		namespace OpenGL {
			class OGLVertexBuffer : public VertexBuffer {
			public:
				OGLVertexBuffer(long size, const void *data);
				void bind() override;
				~OGLVertexBuffer();

				GLuint VBO;
			};
		}
	}
}