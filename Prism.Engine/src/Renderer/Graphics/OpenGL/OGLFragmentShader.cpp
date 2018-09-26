#pragma once;
#include <gl/glew.h>
#include <SDL2/SDL_opengl.h>
#include <iostream> 
#include "Renderer/Graphics/openGL/OGLFragmentShader.h"

using namespace Renderer::Graphics;

namespace Renderer {
	namespace Graphics {
		namespace OpenGL {
			OGLFragmentShader::OGLFragmentShader(const char* source)
			{
				fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

				glShaderSource(fragmentID, 1, &source, NULL);

				glCompileShader(fragmentID);

				GLint fShaderCompiled = GL_FALSE;
				glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &fShaderCompiled);
				if (fShaderCompiled != GL_TRUE)
				{
					printf("Unable to compile fragment shader %d!\n", fragmentID);
				}
			}
			//QQQ Delete shader
			OGLFragmentShader::~OGLFragmentShader()
			{
			}
		}
	}
}