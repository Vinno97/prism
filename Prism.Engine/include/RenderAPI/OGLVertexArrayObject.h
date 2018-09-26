#pragma once
#include <SDL2/SDL_opengl.h>
#include "RenderAPI/VertexArrayObject.h"
#include "RenderAPI/VertexBuffer.h"

namespace RenderAPI {
	class OGLVertexArrayObject: public VertexArrayObject {
	public:
		OGLVertexArrayObject();
		void addVertexBuffer(VertexBuffer* vertexBuffer, int index, long long size, int start, int stride) override;
		void bind() override;
		void unbind() override;
		~OGLVertexArrayObject();
	};
}
