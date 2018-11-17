#pragma once

#include <SDL2/SDL_opengl.h>
#include "Renderer/Graphics/Texture.h"
#include "Surface.h"

namespace Renderer {
	namespace Graphics {
		namespace OpenGL {
			class OGLTexture : public Texture
			{
			public:
				OGLTexture(const char* path);
				void bind() override;
			private:
				GLuint textureID;
			};
		}
	}
}  