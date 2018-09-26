#pragma once
#include <SDL2/SDL_opengl.h>
#include "RenderAPI/RenderDevice.h"
#include "RenderAPI/OGLRenderDevice.h"
#include "RenderAPI/VertexShader.h"
#include "RenderAPI/OGLVertexShader.h"
#include "RenderAPI/OGLFragmentShader.h"
#include "RenderAPI/OGLPipeline.h"
#include "RenderAPI/OGLVertexBuffer.h"
#include "RenderAPI/OGLIndexBuffer.h"
#include "RenderAPI/OGLVertexArrayObject.h"

namespace RenderAPI {
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
