#pragma once
#include <SDL2/SDL_opengl.h>
#include "RenderFacade/RenderDevice.h"
#include "RenderFacade/VertexShader.h"

namespace RenderFacade {
	class OGLRenderDevice : public RenderDevice
	{
	public:
		OGLRenderDevice();
		~OGLRenderDevice();
		VertexShader createVertexShader(const char* source);
	};
}
