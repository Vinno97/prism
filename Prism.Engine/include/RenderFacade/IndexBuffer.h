#pragma once
#include <SDL2/SDL_opengl.h>
namespace RenderFacade {
	class IndexBuffer{
	public:
		IndexBuffer() {};
		virtual void bind() = 0;
	protected:
		GLuint IBO;
	};
}