#pragma once

#include <GL/glew.h>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/VertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLFragmentShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"
#include "Renderer/Graphics/OpenGL/OGLVertexBuffer.h"
#include "Renderer/Graphics/OpenGL/OGLIndexBuffer.h"
#include "Renderer/Graphics/OpenGL/OGLRenderTarget.h"
#include "Renderer/Graphics/OpenGL/OGLVertexArrayObject.h"
#include "Renderer/Graphics/OpenGL/OGLTexture.h"
#include "Renderer/Graphics/OpenGL/OGLGeometryShader.h"
#include <memory>
#include <SDL2/SDL_opengl.h>

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

			unique_ptr<GeometryShader> OGLRenderDevice::createGeometryShader(const char * source) const
			{
				return make_unique<OGLGeometryShader>(source);
			}

			unique_ptr<Pipeline> OGLRenderDevice::createPipeline(VertexShader& vs, FragmentShader& fs) const
			{
				return make_unique<OGLPipeline>(vs, fs);
			}

			std::unique_ptr<Pipeline> OGLRenderDevice::createPipeline(VertexShader & vs, FragmentShader & fs, GeometryShader & gs) const
			{
				return make_unique<OGLPipeline>(vs, fs, gs);
			}

			unique_ptr<VertexBuffer> OGLRenderDevice::createVertexBuffer(long size, const void * data) const
			{
				return make_unique<OGLVertexBuffer>(size, data);
			}

			unique_ptr<VertexBuffer> OGLRenderDevice::createDynamicVertexBuffer() const
			{
				return make_unique<OGLVertexBuffer>();
			}

			unique_ptr<IndexBuffer> OGLRenderDevice::createIndexBuffer(long size, const void * data) const
			{
				return make_unique<OGLIndexBuffer>(size, data);
			}

			unique_ptr<VertexArrayObject> OGLRenderDevice::createVertexArrayobject() const
			{
				return make_unique<OGLVertexArrayObject>();
			}

			std::shared_ptr<Texture> OGLRenderDevice::createTexture(bool depth, int width, int height) const
			{
				return std::make_shared<OGLTexture>(depth, width, height);
			}

			shared_ptr<Texture> OGLRenderDevice::createTexture(const char * path) const
			{
				return make_shared<OGLTexture>(path);
			}

			shared_ptr<Texture> OGLRenderDevice::createTexture(int width, int height, unsigned char* pixels, bool useRGB) const
			{
				return make_shared<OGLTexture>(width, height, pixels, useRGB);
			}

			unique_ptr<RenderTarget> OGLRenderDevice::createRenderTarget(bool useDepthBuffer, int width, int height) const
			{
				return make_unique<OGLRenderTarget>(useDepthBuffer, width, height);
			}

			void OGLRenderDevice::useBlending(const bool blend) const
			{
				if (blend) {
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

			void OGLRenderDevice::setViewPort(const int width, const int height) const
			{
				glViewport(0, 0, width, height);
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