#pragma once
#include <SDL2/SDL_opengl.h>

namespace Renderer
{
	namespace Graphics
	{
		class VertexBuffer
		{
		public:
			VertexBuffer() = default;

			/// <summary>
			/// Make this the current active vertexbuffer
			/// </summary>
			virtual void bind() = 0;

			/// <summary>
			/// Deactivates the vertexbuffer
			/// </summary>
			virtual void unbind() = 0;

			/// <summary>
			/// Rebuffers the vertexbuffer
			/// </summary>
			virtual void rebuffer(long size, const void* data) = 0;
		protected:
			GLuint VBO;
		};
	}
}
