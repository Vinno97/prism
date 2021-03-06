#pragma once
#include <SDL2/SDL_opengl.h>

namespace Renderer {
	namespace Graphics{
		class IndexBuffer {
		public:
			IndexBuffer()=default;

			/// <summary>
			/// Make this the current active indexbuffer
			/// </summary>
			virtual void bind() = 0;
		protected:
			GLuint IBO;
		};
	}
}