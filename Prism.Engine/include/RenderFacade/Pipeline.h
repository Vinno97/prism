#pragma once
#include <SDL2/SDL_opengl.h>

namespace RenderFacade {
	class Pipeline
	{
	public:
		GLuint pipelineID;
		~Pipeline() {};
		Pipeline() {};
		void run() {};
		void stop() {};
	};
}
