#pragma once
#include <SDL2/SDL_opengl.h>

namespace RenderFacade {
	class Pipeline
	{
	public:
		Pipeline() {};
		virtual void run() = 0;
		virtual void stop() = 0;

		GLuint pipelineID;
	};
}
