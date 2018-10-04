#pragma once
#include <SDL2/SDL_opengl.h>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/VertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLFragmentShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"
#include "Renderer/Graphics/OpenGL/OGLVertexBuffer.h"
#include "Renderer/Graphics/OpenGL/OGLIndexBuffer.h"
#include "Renderer/Graphics/OpenGL/OGLVertexArrayObject.h"


namespace Renderer {
	namespace Graphics {
		namespace OpenGL {

			OGLRenderDevice::OGLRenderDevice()
			{
			}
			OGLRenderDevice::~OGLRenderDevice()
			{
				///QQQ Delete all devices and shaders etc
			}

			RenderDevice * OGLRenderDevice::getRenderDevice()
			{
				static OGLRenderDevice instance;
				return &instance;
			}

			VertexShader* OGLRenderDevice::createVertexShader(const char * source)
			{
				return new OGLVertexShader(source);
			}

			FragmentShader* OGLRenderDevice::createFragmentShader(const char * source)
			{
				return new OGLFragmentShader(source);
			}

			Pipeline* OGLRenderDevice::createPipeline(VertexShader* vs, FragmentShader* fs)
			{
				return new OGLPipeline(vs, fs);
			}

			VertexBuffer * OGLRenderDevice::createVertexBuffer(long size, const void * data)
			{
				return new OGLVertexBuffer(size, data);
			}

			IndexBuffer * OGLRenderDevice::createIndexBuffer(long size, const void * data)
			{
				return new OGLIndexBuffer(size, data);
			}

			VertexArrayObject * OGLRenderDevice::createVertexArrayobject()
			{
				return new OGLVertexArrayObject;
			}

			void OGLRenderDevice::setClearColour(float r, float g, float b, float w)
			{
				glClearColor(r, g, b, w);
			}

			void OGLRenderDevice::useDepthTest(bool enable)
			{
				if (enable)
					glEnable(GL_DEPTH_TEST);
				else
					glDisable(GL_DEPTH_TEST);
			}

			void OGLRenderDevice::clearScreen()
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}

			void OGLRenderDevice::DrawTrianglesIndexed(long offset, int count)
			{
				glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, reinterpret_cast<const void *>(offset));
			}
		}
	}
}