#pragma once
#include <SDL2/SDL_opengl.h>
#include "RenderFacade/FragmentShader.h"

namespace RenderFacade {
	class OGLFragmentShader : public FragmentShader
	{
	public:
		OGLFragmentShader(const char* source);
		~OGLFragmentShader();
		bool createUniform(const char* name) override;
		bool setUniformVector(const char* name, float x, float y, float z) override;
	};
}