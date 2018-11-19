#pragma once
#include "Renderer/Graphics/RenderTarget.h"
#include "Renderer/Graphics/Texture.h"
#include <SDL2/SDL_opengl.h>

namespace Renderer {
	namespace Graphics {
		namespace OpenGL {
			class OGLRenderTarget : public RenderTarget {
			public:
				OGLRenderTarget(bool useDepthBuffer, Renderer::Graphics::Texture& texture);
				void bind() override;
				void unbind() override;
				~OGLRenderTarget();

				GLuint FBO;
			};
		}
	}
}