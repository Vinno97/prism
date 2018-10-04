#pragma once
#include <SDL2/SDL_opengl.h>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/VertexShader.h"
#include "Renderer/Graphics/FragmentShader.h"
#include "Renderer/Graphics/Pipeline.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Renderer/Graphics/IndexBuffer.h"
#include "Renderer/Graphics/VertexArrayObject.h"

namespace Renderer {
	namespace Graphics {
		namespace OpenGL {
			class OGLRenderDevice : public RenderDevice
			{
			public:
				OGLRenderDevice();
				~OGLRenderDevice();
				static RenderDevice* getRenderDevice();
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
	}
}