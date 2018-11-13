#pragma once

#include "Renderer/Graphics/Texture.h"

namespace Renderer {
	namespace Graphics {
		namespace OpenGL {
			class OGLTexture : public Renderer::Graphics::Texture
			{
			public:
				OGLTexture();
				~OGLTexture();
			};
		}
	}
}