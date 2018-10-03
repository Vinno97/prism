#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <string>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/VertexShader.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Renderer/Graphics/IndexBuffer.h"

using namespace Renderer::Graphics;

namespace Renderer {
class TestRenderer {
 public:
  TestRenderer();
  void init();
  void draw();
  ~TestRenderer();

 private:
  RenderDevice* renderDevice;
  VertexShader* vertexShader;
  FragmentShader* fragmentShader;
  Pipeline* pipeline;
  VertexBuffer* vertexBuffer;
  IndexBuffer* indexBuffer;

  GLuint gProgramID;
  GLuint gVertexPos2DLocation;
  GLuint gVBO;
  GLuint gIBO;
};
}  // namespace Renderer
