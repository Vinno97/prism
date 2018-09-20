#pragma once
#include <SDL2/SDL_opengl.h>

namespace RenderFacade {
	class Pipeline
	{
	public:
		Pipeline() {};
		virtual void run() = 0;
		virtual void stop() = 0;
		virtual bool createUniform(const char* name) = 0;
		virtual bool setUniformMatrix4f(const char* name, glm::mat4 matrix) = 0;
		virtual bool setUniformVector(const char* name, float x, float y, float z) = 0;
		GLuint pipelineID;
	};
}
