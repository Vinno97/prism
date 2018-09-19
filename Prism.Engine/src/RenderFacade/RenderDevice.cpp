#include "RenderFacade/RenderDevice.h"
#include "RenderFacade/VertexShader.h"

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

}