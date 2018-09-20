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
		VertexShader* createVertexShader(const char* source) override;
		FragmentShader* createFragmentShader(const char* source) override;
		Pipeline* createPipeline(VertexShader* vs, FragmentShader* fs) override;
	};
}
