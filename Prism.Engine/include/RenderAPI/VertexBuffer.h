#pragma once
#include <SDL2/SDL_opengl.h>
namespace RenderAPI {
	class VertexBuffer {
	public:
		VertexBuffer() {};
		virtual void bind() = 0;
	protected:
		GLuint VBO;
	};
}