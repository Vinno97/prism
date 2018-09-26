#pragma once
#include "RenderAPI/IndexBuffer.h"
namespace RenderAPI {
	class OGLIndexBuffer : public IndexBuffer {
	public:
		OGLIndexBuffer(long size, const void *data);
		void bind() override;
		~OGLIndexBuffer();
	};
}