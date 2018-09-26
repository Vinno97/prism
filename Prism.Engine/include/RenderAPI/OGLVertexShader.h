#pragma once
#include <SDL2/SDL_opengl.h>
#include "RenderAPI/VertexShader.h"

namespace RenderAPI {
	class OGLVertexShader : public VertexShader {
	public:
		OGLVertexShader(const char* source);
		~OGLVertexShader();
	};
}
