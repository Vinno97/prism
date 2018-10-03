#pragma once
#include <glm/glm.hpp>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <map>

namespace Renderer {
namespace Graphics {
class VertexShader {
 public:
  VertexShader(){};
  GLuint vertexID;
};
}  // namespace Graphics
}  // namespace Renderer
