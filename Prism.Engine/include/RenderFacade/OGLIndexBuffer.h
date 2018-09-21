#pragma once
#include "RenderFacade/IndexBuffer.h"
namespace RenderFacade {
	class OGLIndexBuffer : public IndexBuffer {
	public:
		OGLIndexBuffer(long size, const void *data);
		void bind() override;
		~OGLIndexBuffer();
	};
}