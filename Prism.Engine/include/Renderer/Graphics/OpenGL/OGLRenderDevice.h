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

using namespace std;

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

				unique_ptr<VertexShader> createVertexShader(const char* source) override;
				unique_ptr<FragmentShader> createFragmentShader(const char* source) override;
				shared_ptr<Pipeline> createPipeline(std::unique_ptr<VertexShader> vs, unique_ptr<FragmentShader> fs) override;
				unique_ptr<VertexBuffer> createVertexBuffer(long size, const void *data) override;
				unique_ptr<IndexBuffer> createIndexBuffer(long size, const void *data) override;
				unique_ptr<VertexArrayObject> createVertexArrayobject() override;

				void setClearColour(float r, float g, float b, float w) override;
				void useDepthTest(bool enable) override;
				void clearScreen() override;
				void DrawTrianglesIndexed(long offset, int count) override;
			private:
				OGLRenderDevice();
			};
		}
	}
}