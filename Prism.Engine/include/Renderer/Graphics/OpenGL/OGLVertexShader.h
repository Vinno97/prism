#pragma once
#include <SDL2/SDL_opengl.h>
#include "Renderer/Graphics/VertexShader.h"

namespace Renderer {
namespace Graphics {
namespace OpenGL {
class OGLVertexShader : public VertexShader {
 public:
  OGLVertexShader(const char* source);
  ~OGLVertexShader();
};
}  // namespace OpenGL
}  // namespace Graphics
}  // namespace Renderer
