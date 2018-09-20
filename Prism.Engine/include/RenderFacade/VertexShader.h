#pragma once
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <map>

namespace RenderFacade {
	class VertexShader {
	public:
		std::map<std::string, int> uniforms;
		VertexShader() {};
		GLuint vertexID;
		virtual bool createUniform(const char* name) = 0;
	};
}
