#pragma once
#include <glm/glm.hpp>
#include <SDL2/SDL_opengl.h>
#include "Renderer/Graphics/VertexBuffer.h"
#include <iostream>
#include <memory>

namespace Renderer {
	namespace Graphics {
		class VertexArrayObject
		{
		public:
			VertexArrayObject()=default;

			/// <summary>
			/// adds a vertexbuffer to the VAO. 
			/// </summary>
			/// <remarks>
			/// Right now this class does not support intervals between strides and different storage types. This may be added when necessary.
			/// </remarks>
			/// <param name="vertexBuffer">Buffer to add to VAO</param>
			/// <param name="index">Position of input variable in the vertex shader</param>
			/// <param name="size">Size of each block of data</param>
			/// <param name="start">Start of the input within the vbo</param>
			/// <param name="stride">Length of the block of data</param>
			virtual void addVertexBuffer(VertexBuffer* vertexBuffer, int index, long long size, int start, int stride) = 0;

			/// <summary>
			/// Make this the current active VAO
			/// </summary>
			virtual void bind() = 0;

			/// <summary>
			/// Deactive the current active VAO
			/// </summary>
			virtual void unbind() = 0;
			GLuint vaoID;
		};
	}
}