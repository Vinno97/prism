#pragma once
#include <SDL2/SDL_opengl.h>
#include "RenderFacade/FragmentShader.h"

namespace RenderFacade {
	class OGLFragmentShader : public FragmentShader
	{
	public:
		OGLFragmentShader(const char* source);
		~OGLFragmentShader();
	};
}