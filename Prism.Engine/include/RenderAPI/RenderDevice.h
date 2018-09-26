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

		/// <summary>
		/// Create a new vertexshader
		/// </summary>
		virtual VertexShader* createVertexShader(const char* source) = 0;

		/// <summary>
		/// Create a new fragmentshader
		/// </summary>
		virtual FragmentShader* createFragmentShader(const char* source) = 0;

		/// <summary>
		/// Create a new pipeline
		/// </summary>
		virtual Pipeline* createPipeline(VertexShader* vs, FragmentShader* fs) = 0;

		/// <summary>
		/// Create a new vertexbuffer
		/// </summary>
		/// <param name="size">Size of the index buffer</param>
		/// <param name="data">Data that the buffer will be filled with (float array)</param>
		virtual VertexBuffer* createVertexBuffer(long size, const void *data) = 0;

		/// <summary>
		/// Create a new indexBuffer
		/// </summary>
		/// <param name="size">Size of the indice buffer</param>
		/// <param name="data">Data that the buffer will be filled with (int array)</param>
		virtual IndexBuffer* createIndexBuffer(long size, const void *data) = 0;

		/// <summary>
		/// Create a new vertexArrayObject
		/// </summary>
		virtual VertexArrayObject* createVertexArrayobject() = 0;
			
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
		/// <param name="count">Amount of indices that is going be drawn</param>
		virtual void DrawTrianglesIndexed(long offset, int count) = 0;
	};
}