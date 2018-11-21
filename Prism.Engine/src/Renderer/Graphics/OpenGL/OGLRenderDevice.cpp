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
#include "Renderer/Graphics/OpenGL/OGLTexture.h"
#include <memory>

using namespace std;

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

			unique_ptr<VertexShader> OGLRenderDevice::createVertexShader(const char * source) const
			{
				return std::make_unique<OGLVertexShader>(source);
			}

			unique_ptr<FragmentShader> OGLRenderDevice::createFragmentShader(const char * source) const
			{
				return make_unique<OGLFragmentShader>(source);
			}

			unique_ptr<Pipeline> OGLRenderDevice::createPipeline(VertexShader& vs, FragmentShader& fs) const
			{
				return make_unique<OGLPipeline>(vs, fs);
			}

			unique_ptr<VertexBuffer> OGLRenderDevice::createVertexBuffer(long size, const void * data) const
			{
				return make_unique<OGLVertexBuffer>(size, data);
			}

			unique_ptr<IndexBuffer> OGLRenderDevice::createIndexBuffer(long size, const void * data) const
			{
				return make_unique<OGLIndexBuffer>(size, data);
			}

			unique_ptr<VertexArrayObject> OGLRenderDevice::createVertexArrayobject() const
			{
				return make_unique<OGLVertexArrayObject>();
			}

			shared_ptr<Texture> OGLRenderDevice::createTexture(const char * path) const
			{
				return make_shared<OGLTexture>(path);
			}

			void OGLRenderDevice::useBlending(const bool blend) const
			{
				if (true) {
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				}
				else {
					glDisable(GL_BLEND);
				}
			}

			void OGLRenderDevice::setClearColour(float r, float g, float b, float w) const
			{
				glClearColor(r, g, b, w);
			}

			void OGLRenderDevice::useDepthTest(bool enable) const
			{
				if (enable)
					glEnable(GL_DEPTH_TEST);
				else
					glDisable(GL_DEPTH_TEST);
			}

			void OGLRenderDevice::clearScreen() const
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}

			void OGLRenderDevice::DrawTrianglesIndexed(long offset, int count) const
			{
				glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, reinterpret_cast<const void *>(offset));
			}
			void OGLRenderDevice::DrawTriangles(long offset, int count) const
			{
				glDrawArrays(GL_TRIANGLES, 0, count);
			}
		}
	}
}