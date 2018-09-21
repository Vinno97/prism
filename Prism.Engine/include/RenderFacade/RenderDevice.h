#pragma once
#include <SDL2/SDL_opengl.h>
#include "RenderFacade/VertexShader.h"
#include "RenderFacade/FragmentShader.h"
#include "RenderFacade/Pipeline.h"
#include "RenderFacade/VertexBuffer.h"
#include "RenderFacade/IndexBuffer.h"

namespace RenderFacade {
	class RenderDevice
	{
	public:
		RenderDevice() {};
		~RenderDevice() {};
		virtual VertexShader* createVertexShader(const char* source) = 0;
		virtual FragmentShader* createFragmentShader(const char* source) = 0;
		virtual Pipeline* createPipeline(VertexShader* vs, FragmentShader* fs) = 0;
		virtual VertexBuffer* createVertexBuffer(long size, const void *data) = 0;
		virtual IndexBuffer* createIndexBuffer(long size, const void *data) = 0;
		virtual void clearScreen() = 0;
		virtual void DrawTrianglesIndexed(long offset, int count) = 0;
	};
}