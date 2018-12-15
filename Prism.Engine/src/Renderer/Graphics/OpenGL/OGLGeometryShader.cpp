#pragma once;
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <iostream> 
#include <string>
#include "Renderer/Graphics/OpenGL/OGLGeometryShader.h"

using namespace Renderer::Graphics;

namespace Renderer {
	namespace Graphics {
		namespace OpenGL {
			OGLGeometryShader::OGLGeometryShader(const char* source)
			{
				geometryID = glCreateShader(GL_GEOMETRY_SHADER);

				glShaderSource(geometryID, 1, &source, NULL);

				glCompileShader(geometryID);

				GLint fShaderCompiled = GL_FALSE;
				glGetShaderiv(geometryID, GL_COMPILE_STATUS, &fShaderCompiled);
				if (fShaderCompiled != GL_TRUE)
				{
					int infologLength = 0;

					int charsWritten = 0;
					char *infoLog;

					glGetShaderiv(geometryID, GL_INFO_LOG_LENGTH, &infologLength);

					infoLog = (char *)malloc(infologLength);
					glGetShaderInfoLog(geometryID, infologLength, &charsWritten, infoLog);

					std::string log = infoLog;

					std::cerr << "Unable to compile fragment shader " << log;
					throw std::runtime_error("Fragment shader does not compile");
				}
			}
		}
	}
}