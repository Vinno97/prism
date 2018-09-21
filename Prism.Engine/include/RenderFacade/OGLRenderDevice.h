#pragma once
#include <SDL2/SDL_opengl.h>
#include "RenderFacade/RenderDevice.h"
#include "RenderFacade/VertexShader.h"
#include "RenderFacade/FragmentShader.h"
#include "RenderFacade/Pipeline.h"
#include "RenderFacade/VertexBuffer.h"
#include "RenderFacade/IndexBuffer.h"

namespace RenderFacade {
	class OGLRenderDevice : public RenderDevice
	{
	public:
		OGLRenderDevice();
		~OGLRenderDevice();
		VertexShader* createVertexShader(const char* source) override;
		FragmentShader* createFragmentShader(const char* source) override;
		Pipeline* createPipeline(VertexShader* vs, FragmentShader* fs) override;
		VertexBuffer* createVertexBuffer(long size, const void *data) override;
		IndexBuffer* createIndexBuffer(long size, const void *data) override;
		void clearScreen() override;
		void DrawTrianglesIndexed(long offset, int count) override;
	};
}
