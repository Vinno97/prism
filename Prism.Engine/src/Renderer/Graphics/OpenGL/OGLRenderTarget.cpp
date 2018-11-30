#pragma once
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "Renderer/Graphics/OpenGL/OGLRenderTarget.h"
#include <iostream> 

namespace Renderer {
	namespace Graphics {
		namespace OpenGL {
			OGLRenderTarget::OGLRenderTarget(bool useDepthBuffer) {
				glGenFramebuffers(1, &FBO);
				glBindFramebuffer(GL_FRAMEBUFFER, FBO);

				if (useDepthBuffer) {
					GLuint depthrenderbuffer;
					glGenRenderbuffers(1, &depthrenderbuffer);
					glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
					glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1920, 1080);
					glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);
				}

				unbind();
			}

			void OGLRenderTarget::bind()
			{
				GLenum* drawBuffers = new GLenum[bufferAmount];
				for (int i = 0; i < bufferAmount; i++) {
					drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
				}

				glBindFramebuffer(GL_FRAMEBUFFER, FBO);
				glDrawBuffers(bufferAmount, drawBuffers);
				
				delete drawBuffers;
			}

			void OGLRenderTarget::unbind()
			{
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}

			void OGLRenderTarget::addBuffer(std::shared_ptr<Texture> texture)
			{
				bind();
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+bufferAmount, GL_TEXTURE_2D, texture->getID(), 0);
				bufferAmount++;
				unbind();
			}

			void OGLRenderTarget::setDepthBuffer(std::shared_ptr<Texture> texture)
			{
				bind();
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture->getID(), 0);
				unbind();
			}

			int OGLRenderTarget::getID()
			{
				return FBO;
			}

			OGLRenderTarget::~OGLRenderTarget()
			{
				glDeleteBuffers(1, &FBO);
			}
		};
	}
}