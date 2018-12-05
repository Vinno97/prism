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

			OGLTexture::OGLTexture(bool depth)
			{
				glGenTextures(1, &textureID);
				glBindTexture(GL_TEXTURE_2D, textureID);

				// Give an empty image to OpenGL ( the last "0" )
				if (depth) {
					glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1920/2, 1080/2, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
				}
				else {
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1920/2, 1080/2, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
				}

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
			}

			int OGLTexture::getID()
			{
				return textureID;
			}

			void OGLTexture::bind(int target)
			{
				glActiveTexture(target);
				glBindTexture(GL_TEXTURE_2D, textureID);
			}
		}
	}
}
