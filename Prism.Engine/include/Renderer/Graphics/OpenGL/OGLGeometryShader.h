#pragma once
#include <SDL2/SDL_opengl.h>
#include "Renderer/Graphics/GeometryShader.h"

namespace Renderer {
	namespace Graphics {
		namespace OpenGL {
			class OGLGeometryShader : public GeometryShader
			{
			public:
				OGLGeometryShader(const char* source);
			};
		}
	}
}