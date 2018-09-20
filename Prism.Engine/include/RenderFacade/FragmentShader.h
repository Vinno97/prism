#pragma once
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <map>

namespace RenderFacade {
	class FragmentShader {
	public:
		std::map<std::string, int> uniforms;
		GLuint fragmentID;
		virtual bool createUniform(const char* name) = 0;
		virtual bool setUniformVector(const char* name, float x, float y, float z) = 0;
	};
}
