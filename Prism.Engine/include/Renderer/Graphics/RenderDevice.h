#pragma once
#include <SDL2/SDL_opengl.h>
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
		class RenderDevice
		{
		public:
			RenderDevice() {};
			~RenderDevice() {};

			/// <summary>
			/// Create a new vertexshader
			/// </summary>
			virtual unique_ptr<VertexShader> createVertexShader(const char* source) = 0;

			/// <summary>
			/// Create a new fragmentshader
			/// </summary>
			virtual unique_ptr<FragmentShader> createFragmentShader(const char* source) = 0;

			/// <summary>
			/// Create a new pipeline
			/// </summary>
			virtual unique_ptr<Pipeline> createPipeline(VertexShader& vs, FragmentShader& fs) = 0;

			/// <summary>
			/// Create a new vertexbuffer
			/// </summary>
			/// <param name="size">Size of the index buffer</param>
			/// <param name="data">Data that the buffer will be filled with (float array)</param>
			virtual unique_ptr<VertexBuffer> createVertexBuffer(long size, const void *data) = 0;

			/// <summary>
			/// Create a new indexBuffer
			/// </summary>
			/// <param name="size">Size of the indice buffer</param>
			/// <param name="data">Data that the buffer will be filled with (int array)</param>
			virtual unique_ptr<IndexBuffer> createIndexBuffer(long size, const void *data) = 0;

			/// <summary>
			/// Create a new vertexArrayObject
			/// </summary>
			virtual unique_ptr<VertexArrayObject> createVertexArrayobject() = 0;

			/// <summary>
			/// Set the colour that the screen will be cleared with
			/// </summary>
			virtual void setClearColour(float r, float g, float b, float w) = 0;

			/// <summary>
			/// Enable/disable depth testing
			/// </summary>
			virtual void useDepthTest(bool enable) = 0;

			/// <summary>
			/// clear the screen
			/// </summary>
			virtual void clearScreen() = 0;

			/// <summary>
			/// Draw the currently bound VBO's using indices 
			/// </summary>
			/// <param name="offset">Offset of the drawing call</param>
			/// <param name="count">Amount of indices that are going to be drawn</param>
			virtual void DrawTrianglesIndexed(long offset, int count) = 0;
		};
	}
}