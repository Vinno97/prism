#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include <iostream>
#include <string>

namespace Renderer
{
	namespace Graphics
	{
		namespace OpenGL
		{
			OGLVertexShader::OGLVertexShader(const char* source)
			{
				//Create vertex shader
				vertexID = glCreateShader(GL_VERTEX_SHADER);

				//Set vertex source
				glShaderSource(vertexID, 1, &source, nullptr);

				//Compile vertex source
				glCompileShader(vertexID);

				GLint fShaderCompiled = GL_FALSE;
				glGetShaderiv(vertexID, GL_COMPILE_STATUS, &fShaderCompiled);
				if (fShaderCompiled != GL_TRUE)
				{
					int infologLength = 0;

					int charsWritten = 0;
					char* infoLog;

					glGetShaderiv(vertexID, GL_INFO_LOG_LENGTH, &infologLength);

					infoLog = (char *)malloc(infologLength);
					glGetShaderInfoLog(vertexID, infologLength, &charsWritten, infoLog);

					std::string log = infoLog;

					std::cerr << "Unable to compile vertex shader " << log;
					throw std::runtime_error("Vertex shader does not compile");
				}
			}

			OGLVertexShader::~OGLVertexShader()
			{
			}
		}
	}
}
