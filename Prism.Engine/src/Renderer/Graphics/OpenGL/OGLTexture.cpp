#include "Renderer/Graphics/OpenGL/OGLTexture.h"

namespace Renderer {
	namespace Graphics {
		namespace OpenGL {
			OGLTexture::OGLTexture(const char* path)
			{
				Surface surface = Surface{ path };

				int mode = GL_RGB;
				if (surface.bytesperPixel() == 4) {
					mode = GL_RGBA;
				}

				glGenTextures(1, &textureID);
				glBindTexture(GL_TEXTURE_2D, textureID);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glTexImage2D(GL_TEXTURE_2D, 0, mode, surface.width(), surface.height(), 0, mode, GL_UNSIGNED_BYTE, surface.pixels()); //GL_BITMAP

			}
			void OGLTexture::bind()
			{
				glBindTexture(GL_TEXTURE_2D, textureID);
			}
		}
	}
}
