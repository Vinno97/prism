#pragma once
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "Renderer/Graphics/OpenGL/OGLRenderTarget.h"
#include <iostream> 

namespace Renderer {
	namespace Graphics {
		namespace OpenGL {
			OGLRenderTarget::OGLRenderTarget(bool useDepthBuffer, Renderer::Graphics::Texture& texture) {
				glGenFramebuffers(1, &FBO);
				glBindFramebuffer(GL_FRAMEBUFFER, FBO);

				if (useDepthBuffer) {
					GLuint depthrenderbuffer;
					glGenRenderbuffers(1, &depthrenderbuffer);
					glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
					glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
					glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);
				}

				// Set "renderedTexture" as our colour attachement #0
				glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture.getID() , 0);

				// Set the list of draw buffers.
				GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
				glDrawBuffers(1, DrawBuffers);
			}

			void OGLRenderTarget::bind()
			{
				glBindFramebuffer(GL_FRAMEBUFFER, FBO);
			}

			void OGLRenderTarget::unbind()
			{
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}

			OGLRenderTarget::~OGLRenderTarget()
			{
				glDeleteBuffers(1, &FBO);
			}
		};
	}
}