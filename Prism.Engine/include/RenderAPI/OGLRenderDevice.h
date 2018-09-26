#pragma once
#include <SDL2/SDL_opengl.h>
#include "RenderAPI/RenderDevice.h"
#include "RenderAPI/VertexShader.h"
#include "RenderAPI/FragmentShader.h"
#include "RenderAPI/Pipeline.h"
#include "RenderAPI/VertexBuffer.h"
#include "RenderAPI/IndexBuffer.h"
#include "RenderAPI/VertexArrayObject.h"

namespace RenderAPI {
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
		VertexArrayObject* createVertexArrayobject() override;

		void setClearColour(float r, float g, float b, float w) override;
		void useDepthTest(bool enable) override;
		void clearScreen() override;
		void DrawTrianglesIndexed(long offset, int count) override;
	};
}
