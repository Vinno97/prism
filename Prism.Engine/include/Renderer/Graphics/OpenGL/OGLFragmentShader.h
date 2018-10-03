#pragma once
#include <SDL2/SDL_opengl.h>
#include "Renderer/Graphics/FragmentShader.h"

namespace Renderer {
	namespace Graphics {
		namespace OpenGL {
			class OGLFragmentShader : public FragmentShader
			{
			public:
				OGLFragmentShader(const char* source);
				~OGLFragmentShader();
			};
		}
	}
}