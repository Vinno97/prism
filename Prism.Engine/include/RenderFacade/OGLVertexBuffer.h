#pragma once
#include "RenderFacade/VertexBuffer.h"
namespace RenderFacade {
	class OGLVertexBuffer : public VertexBuffer {
	public:
		OGLVertexBuffer(long size, const void *data);
		void bind() override;
		~OGLVertexBuffer();
	};
}