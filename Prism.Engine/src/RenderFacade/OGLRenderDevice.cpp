#pragma once
#include <SDL2/SDL_opengl.h>
#include "RenderFacade/RenderDevice.h"
#include "RenderFacade/OGLRenderDevice.h"
#include "RenderFacade/VertexShader.h"
#include "RenderFacade/OGLVertexShader.h"
#include "RenderFacade/OGLFragmentShader.h"
#include "RenderFacade/OGLPipeline.h"

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
}
