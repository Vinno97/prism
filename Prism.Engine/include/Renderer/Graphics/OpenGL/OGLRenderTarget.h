#pragma once
#include "Renderer/Graphics/RenderTarget.h"
#include "Renderer/Graphics/Texture.h"
#include "Renderer/Graphics/OpenGL/OGlTexture.h"
#include <vector>
#include <SDL2/SDL_opengl.h>

namespace Renderer {
	namespace Graphics {
		namespace OpenGL {
			class OGLRenderTarget : public RenderTarget {
			public:
				OGLRenderTarget(bool useDepthBuffer);
				void bind() override;
				void unbind() override;
				void addBuffer(std::shared_ptr<Texture> texture) override;
				void setDepthBuffer(std::shared_ptr<Texture> texture) override;
				int getID();
				~OGLRenderTarget();

				GLuint FBO;
			private:
				int bufferAmount = 0;
			};
		}
	}
}