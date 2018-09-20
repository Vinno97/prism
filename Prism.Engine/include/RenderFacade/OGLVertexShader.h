#pragma once
#include <SDL2/SDL_opengl.h>
#include "RenderFacade/VertexShader.h"

namespace RenderFacade {
	class OGLVertexShader : public VertexShader {
	public:
		OGLVertexShader(const char* source);
		~OGLVertexShader();
		bool createUniform(const char* name);
		//int vertexID;
	};
}
