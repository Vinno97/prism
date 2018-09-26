#pragma once
#include <SDL2/SDL_opengl.h>
#include "RenderAPI/VertexShader.h"
#include "RenderAPI/FragmentShader.h"
#include "RenderAPI/Pipeline.h"
#include "RenderAPI/VertexBuffer.h"
#include "RenderAPI/IndexBuffer.h"
#include "RenderAPI/VertexArrayObject.h"

namespace RenderAPI {
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
		virtual VertexArrayObject* createVertexArrayobject() = 0;
		virtual void setClearColour(float r, float g, float b, float w) = 0;
		virtual void useDepthTest(bool enable) = 0;
		virtual void clearScreen() = 0;
		virtual void DrawTrianglesIndexed(long offset, int count) = 0;
	};
}