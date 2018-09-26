#pragma once
#include <SDL2/SDL_opengl.h>
namespace RenderAPI {
	class IndexBuffer{
	public:
		IndexBuffer() {};

		/// <summary>
		/// Make this the current active indexbuffer
		/// </summary>
		virtual void bind() = 0;
	protected:
		GLuint IBO;
	};
}