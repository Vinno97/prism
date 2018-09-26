#pragma once
#include <glm/glm.hpp>
#include <SDL2/SDL_opengl.h>
#include "RenderAPI/VertexBuffer.h"
#include <iostream>

namespace RenderAPI {
	class VertexArrayObject
	{
	public:
		VertexArrayObject() {};
		virtual void addVertexBuffer(VertexBuffer* vertexBuffer, int index, long long size, int start, int stride) = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;
		GLuint vaoID;
	};
}
