#pragma once
#include <SDL2/SDL_opengl.h>

namespace RenderFacade {
	class VertexShader {
	public:
		GLuint vertexID;
		bool createUniform(const char* name) { return false; };
	};
}
