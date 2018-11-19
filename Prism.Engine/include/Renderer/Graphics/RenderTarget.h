#pragma once
#include <SDL2/SDL_opengl.h>

namespace Renderer {
	namespace Graphics {
		class RenderTarget {
		public:
			RenderTarget() = default;

			/// <summary>
			/// Make this the current active rendertarget
			/// </summary>
			virtual void bind() = 0;

			/// <summary>
			/// Make this the current active rendertarget
			/// </summary>
			virtual void unbind() = 0;
		protected:
			GLuint FBO;
		};
	}
}