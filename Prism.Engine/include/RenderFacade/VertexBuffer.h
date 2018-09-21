#pragma once
#include <SDL2/SDL_opengl.h>
namespace RenderFacade {
	class VertexBuffer {
	public:
		VertexBuffer() {};
		virtual void bind() = 0;
	protected:
		GLuint VBO;
	};
}