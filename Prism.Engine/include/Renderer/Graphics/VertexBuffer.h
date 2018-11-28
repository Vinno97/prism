#pragma once
#include <SDL2/SDL_opengl.h>

namespace Renderer {
	namespace Graphics {
		class VertexBuffer {
		public:
			VertexBuffer()=default;

			/// <summary>
			/// Make this the current active vertexbuffer
			/// </summary>
			virtual void bind() = 0;
		protected:
			GLuint VBO;
		};
	}
}