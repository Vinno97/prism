#pragma once
#include <SDL2/SDL_opengl.h>
#include "Renderer/Graphics/VertexShader.h"
#include "Renderer/Graphics/FragmentShader.h"
#include "Renderer/Graphics/Pipeline.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Renderer/Graphics/IndexBuffer.h"
#include "Renderer/Graphics/Texture.h"
#include "Renderer/Graphics/VertexArrayObject.h"
#include "Renderer/Graphics/RenderTarget.h"
#include <memory>

namespace Renderer {
	namespace Graphics {
		class RenderDevice
		{
		public:
			RenderDevice()=default;
			~RenderDevice()=default;

			/// <summary>
			/// Create a new vertexshader
			/// </summary>
			virtual std::unique_ptr<VertexShader> createVertexShader(const char* source) const = 0;

			/// <summary>
			/// Create a new fragmentshader
			/// </summary>
			virtual std::unique_ptr<FragmentShader> createFragmentShader(const char* source)  const = 0;

			/// <summary>
			/// Create a new pipeline
			/// </summary>
			virtual std::unique_ptr<Pipeline> createPipeline(VertexShader& vs, FragmentShader& fs) const = 0;

			/// <summary>
			/// Create a new vertexbuffer
			/// </summary>
			/// <param name="size">Size of the index buffer</param>
			/// <param name="data">Data that the buffer will be filled with (float array)</param>
			virtual std::unique_ptr<VertexBuffer> createVertexBuffer(long size, const void *data) const = 0;

			/// <summary>
			/// Create a new dynamic vertexbuffer
			/// </summary>
			virtual std::unique_ptr<VertexBuffer> createDynamicVertexBuffer() const = 0;

			/// <summary>
			/// Create a new indexBuffer
			/// </summary>
			/// <param name="size">Size of the indice buffer</param>
			/// <param name="data">Data that the buffer will be filled with (int array)</param>
			virtual std::unique_ptr<IndexBuffer> createIndexBuffer(long size, const void *data) const = 0;

			/// <summary>
			/// Create a new vertexArrayObject
			/// </summary>
			virtual std::unique_ptr<VertexArrayObject> createVertexArrayobject() const = 0;

			/// <summary>
			/// Create a new vertexArrayObject
			/// </summary>
			virtual std::unique_ptr<RenderTarget> createRenderTarget(bool useDepthBuffer, std::shared_ptr<Texture> texture) const = 0;

			/// <summary>
			/// Create a new texture with image path
			/// </summary>
			virtual std::shared_ptr<Texture> createTexture(const char* path) const = 0;

			/// <summary>
			/// Create a new texture with width and height
			/// </summary>
			virtual std::shared_ptr<Texture> createTexture(int width, int height, unsigned char* pixels, bool useRGB) const = 0;

			/// <summary>
			/// Create a new texture 
			/// </summary>
			virtual std::shared_ptr<Texture> createTexture() const = 0;

			/// <summary>
			/// Set the colour that the screen will be cleared with
			/// </summary>
			virtual void setClearColour(float r, float g, float b, float w) const = 0;

			/// <summary>
			/// Enable/disable depth testing
			/// </summary>
			virtual void useDepthTest(bool enable) const = 0;

			/// <summary>
			/// clear the screen
			/// </summary>
			virtual void clearScreen() const = 0;

			/// <summary>
			/// Toggle blending mode
			/// </summary>
			virtual void useBlending(const bool blend) const = 0;

			/// <summary>
			/// Draw the currently bound VBO's using indices 
			/// </summary>
			/// <param name="offset">Offset of the drawing call</param>
			/// <param name="count">Amount of indices that are going to be drawn</param>
			virtual void DrawTrianglesIndexed(long offset, int count) const = 0;

			/// <summary>
			/// Draw the currently bound VBO's
			/// </summary>
			/// <param name="offset">Offset of the drawing call</param>
			/// <param name="count">Amount of vertices that are going to be drawn</param>
			virtual void DrawTriangles(long offset, int count) const = 0;
		};
	}
}