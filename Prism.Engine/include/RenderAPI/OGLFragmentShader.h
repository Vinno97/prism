#pragma once
#include <SDL2/SDL_opengl.h>
#include "RenderAPI/FragmentShader.h"

namespace RenderAPI {
	class OGLFragmentShader : public FragmentShader
	{
	public:
		OGLFragmentShader(const char* source);
		~OGLFragmentShader();
	};
}