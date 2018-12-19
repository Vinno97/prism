#pragma once
#include <SDL2/SDL_opengl.h>
#include "Renderer/Graphics/VertexArrayObject.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include <memory>

namespace Renderer {
	namespace Graphics {
		namespace OpenGL {
			class OGLVertexArrayObject : public VertexArrayObject {
			public:
				OGLVertexArrayObject();
				void addVertexBuffer(VertexBuffer* vertexBuffer, int index, long long size, int start, int stride) override;
				void bind() override;
				void unbind() override;
				~OGLVertexArrayObject();
			};
		}
	}
}