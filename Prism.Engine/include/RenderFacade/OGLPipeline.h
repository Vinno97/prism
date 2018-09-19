#pragma once
#include "RenderFacade/Pipeline.h"
#include "RenderFacade/VertexShader.h"
#include "RenderFacade/FragmentShader.h"

namespace RenderFacade {
	class OGLPipeline : public Pipeline
	{
	public:
		OGLPipeline(VertexShader vs, FragmentShader fs);
		~OGLPipeline();
		void run();	
		void stop();
	};
}
