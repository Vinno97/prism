#pragma once
#include <GL/glew.h>
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
				OGLTexture(bool depth, int width, int height);
				OGLTexture(int width, int height, unsigned char* pixels, bool useRGB);
				int getID() override;
				void bind(int target) override;
			private:
				GLuint textureID;
			};
		}
	}
}  