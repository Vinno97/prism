#pragma once
#include <SDL2/SDL_opengl.h>
#include "RenderFacade/RenderDevice.h"
#include "RenderFacade/OGLRenderDevice.h"
#include "RenderFacade/VertexShader.h"
#include "RenderFacade/OGLVertexShader.h"

namespace RenderFacade {
	OGLRenderDevice::OGLRenderDevice()
	{
	}
	OGLRenderDevice::~OGLRenderDevice()
	{
	}
	VertexShader OGLRenderDevice::createVertexShader(const char * source)
	{
		return VertexShader();
	}
	//VertexShader OGLRenderDevice::createVertexShader(const char* source)
	//{
	//	return OGLVertexShader(source);
	//}
}
