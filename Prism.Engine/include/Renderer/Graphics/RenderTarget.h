#pragma once
#include <SDL2/SDL_opengl.h>
#include "Renderer/Graphics/Texture.h"
#include <memory>

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

			/// <summary>
			/// Add a colourbuffer to be drawn to
			/// </summary>
			virtual void addBuffer(std::shared_ptr<Texture> texture) = 0;
		protected:
			GLuint FBO;
		};
	}
}