#pragma once;
#include <gl/glew.h>
#include <SDL2/SDL_opengl.h>
#include <iostream> 
#include <string>
#include "Renderer/Graphics/openGL/OGLFragmentShader.h"

using namespace Renderer::Graphics;

namespace Renderer {
	namespace Graphics {
		namespace OpenGL {
			OGLFragmentShader::OGLFragmentShader(const char* source)
			{
				fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

				glShaderSource(fragmentID, 1, &source, nullptr);

				glCompileShader(fragmentID);

				GLint fShaderCompiled = GL_FALSE;
				glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &fShaderCompiled);
				if (fShaderCompiled != GL_TRUE)
				{
					int infologLength = 0;

					int charsWritten  = 0;
					char *infoLog;

					glGetShaderiv(fragmentID, GL_INFO_LOG_LENGTH,&infologLength);

					infoLog = static_cast<char *>(malloc(infologLength));
					glGetShaderInfoLog(fragmentID, infologLength, &charsWritten, infoLog);

					std::string log = infoLog;

					std::cerr << "Unable to compile fragment shader " << log;
					throw std::runtime_error("Fragment shader does not compile");
				}
			}
			//QQQ Delete shader
			OGLFragmentShader::~OGLFragmentShader()
			= default;
		}  // namespace OpenGL
	}  // namespace Graphics
}  // namespace Renderer