#pragma once
#include <SDL2/SDL_opengl.h>
#include "RenderFacade/VertexShader.h"

namespace RenderFacade {
	class RenderDevice
	{
	public:
		RenderDevice();
		~RenderDevice();
		virtual VertexShader createVertexShader(const char* source);
	};
}