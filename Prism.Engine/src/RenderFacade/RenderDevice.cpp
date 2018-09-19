#include "RenderFacade/RenderDevice.h"
#include "RenderFacade/VertexShader.h"
#include "RenderFacade/FragmentShader.h"
#include "RenderFacade/Pipeline.h"

namespace RenderFacade {

	RenderFacade::RenderDevice::RenderDevice()
	{
	}

	RenderFacade::RenderDevice::~RenderDevice()
	{
	}

	VertexShader RenderDevice::createVertexShader(const char* source) {
		return VertexShader();
	}

	FragmentShader RenderDevice::createFragmentShader(const char* source) {
		return FragmentShader();
	}
	
	Pipeline RenderDevice::createPipeline(VertexShader vs, FragmentShader fs) {
		return Pipeline();
	}

}