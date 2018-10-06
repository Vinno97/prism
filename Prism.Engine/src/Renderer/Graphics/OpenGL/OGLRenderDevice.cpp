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

			unique_ptr<VertexShader> OGLRenderDevice::createVertexShader(const char * source)
			{
				return std::make_unique<OGLVertexShader>(source);
			}

			unique_ptr<FragmentShader> OGLRenderDevice::createFragmentShader(const char * source)
			{
				return make_unique<OGLFragmentShader>(source);
			}

			shared_ptr<Pipeline> OGLRenderDevice::createPipeline(unique_ptr<VertexShader> vs, unique_ptr<FragmentShader> fs)
			{
				return make_shared<OGLPipeline>(move(vs), move(fs));
			}

			unique_ptr<VertexBuffer> OGLRenderDevice::createVertexBuffer(long size, const void * data)
			{
				return make_unique<OGLVertexBuffer>(size, data);
			}

			unique_ptr<IndexBuffer> OGLRenderDevice::createIndexBuffer(long size, const void * data)
			{
				return make_unique<OGLIndexBuffer>(size, data);
			}

			unique_ptr<VertexArrayObject> OGLRenderDevice::createVertexArrayobject()
			{
				return make_unique<OGLVertexArrayObject>();
			}

			void OGLRenderDevice::setClearColour(float r, float g, float b, float w)
			{
				glClearColor(r, g, b, w);
			}

			void OGLRenderDevice::useDepthTest(bool enable)
			{

				glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT);
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