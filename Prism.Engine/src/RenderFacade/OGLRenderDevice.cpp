#pragma once
#include <SDL2/SDL_opengl.h>
#include "RenderFacade/RenderDevice.h"
#include "RenderFacade/OGLRenderDevice.h"
#include "RenderFacade/VertexShader.h"
#include "RenderFacade/OGLVertexShader.h"
#include "RenderFacade/OGLFragmentShader.h"
#include "RenderFacade/OGLPipeline.h"
#include "RenderFacade/OGLVertexBuffer.h"
#include "RenderFacade/OGLIndexBuffer.h"

namespace RenderFacade {
	OGLRenderDevice::OGLRenderDevice()
	{
	}
	OGLRenderDevice::~OGLRenderDevice()
	{
		///QQQ Delete all devices and shaders etc
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

	void OGLRenderDevice::clearScreen()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OGLRenderDevice::DrawTrianglesIndexed(long offset, int count)
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, reinterpret_cast<const void *>(offset));
	}
}
