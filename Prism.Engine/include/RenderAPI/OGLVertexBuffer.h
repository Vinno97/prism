#pragma once
#include "RenderAPI/VertexBuffer.h"
#include <SDL2/SDL_opengl.h>
namespace RenderAPI {
	class OGLVertexBuffer : public VertexBuffer {
	public:
		OGLVertexBuffer(long size, const void *data);
		void bind() override;
		~OGLVertexBuffer();

		GLuint VBO;
	};
}