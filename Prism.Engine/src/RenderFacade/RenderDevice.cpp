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
		throw "Method should not be called";
	}

	FragmentShader RenderDevice::createFragmentShader(const char* source) {
		throw "Method should not be called";
	}
	
	Pipeline RenderDevice::createPipeline(VertexShader vs, FragmentShader fs) {
		throw "Method should not be called";
	}

}