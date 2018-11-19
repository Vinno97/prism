#pragma once
#include <SDL2/SDL_opengl.h>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/VertexShader.h"
#include "Renderer/Graphics/FragmentShader.h"
#include "Renderer/Graphics/Pipeline.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Renderer/Graphics/IndexBuffer.h"
#include "Renderer/Graphics/VertexArrayObject.h"
#include <memory>

namespace Renderer {
	namespace Graphics {
		namespace OpenGL {
			class OGLRenderDevice : public RenderDevice
			{
			public:
				~OGLRenderDevice();

				/// <summary>
				/// Returns the renderdevice
				/// </summary>
				/// <remarks>
				/// As a static method cannot be overriden this is not defined in the base class
				/// </remarks>
				static RenderDevice* getRenderDevice();

				std::unique_ptr<VertexShader> createVertexShader(const char* source) const override;
				std::unique_ptr<FragmentShader> createFragmentShader(const char* source) const override;
				std::unique_ptr<Pipeline> createPipeline(VertexShader& vs, FragmentShader& fs) const override;
				std::unique_ptr<VertexBuffer> createVertexBuffer(long size, const void *data) const override;
				std::unique_ptr<IndexBuffer> createIndexBuffer(long size, const void *data) const override;
				std::unique_ptr<VertexArrayObject> createVertexArrayobject() const override;

				void setClearColour(float r, float g, float b, float w) const override;
				void useDepthTest(bool enable) const override;
				void clearScreen() const override;
				void DrawTrianglesIndexed(long offset, int count) const override;
				void DrawTriangles(long offset, int count) const override;
			private:
				OGLRenderDevice();
			};
		}
	}
}