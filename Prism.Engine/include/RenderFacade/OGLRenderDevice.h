#pragma once
#include <SDL2/SDL_opengl.h>
#include "RenderFacade/RenderDevice.h"
#include "RenderFacade/VertexShader.h"
#include "RenderFacade/FragmentShader.h"
#include "RenderFacade/Pipeline.h"

namespace RenderFacade {
	class OGLRenderDevice : public RenderDevice
	{
	public:
		OGLRenderDevice();
		~OGLRenderDevice();
		virtual VertexShader createVertexShader(const char* source);
		virtual FragmentShader createFragmentShader(const char* source);
		virtual Pipeline createPipeline(VertexShader vs, FragmentShader fs);
	};
}
