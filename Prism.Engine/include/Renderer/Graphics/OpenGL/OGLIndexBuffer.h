#pragma once
#include "Renderer/Graphics/IndexBuffer.h"
namespace Renderer {
namespace Graphics {
namespace OpenGL {
class OGLIndexBuffer : public IndexBuffer {
 public:
  OGLIndexBuffer(long size, const void* data);
  void bind() override;
  ~OGLIndexBuffer();
};
}  // namespace OpenGL
}  // namespace Graphics
}  // namespace Renderer
