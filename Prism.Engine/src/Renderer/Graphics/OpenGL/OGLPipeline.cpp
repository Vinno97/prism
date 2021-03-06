#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL2/SDL_opengl.h>
#include "Renderer/Graphics/VertexShader.h"
#include "Renderer/Graphics/FragmentShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;

namespace Renderer {
	namespace Graphics {
		namespace OpenGL {
			OGLPipeline::OGLPipeline(VertexShader& vs, FragmentShader& fs)
			{
				pipelineID = glCreateProgram();
				glAttachShader(pipelineID, vs.vertexID);
				glAttachShader(pipelineID, fs.fragmentID);
				glLinkProgram(pipelineID);
				GLint programSuccess = GL_TRUE;
				glGetProgramiv(pipelineID, GL_LINK_STATUS, &programSuccess);

				if (programSuccess != GL_TRUE)
				{
					int infologLength = 0;

					int charsWritten  = 0;
					char *infoLog;

					glGetProgramiv(pipelineID, GL_INFO_LOG_LENGTH,&infologLength);

					infoLog = (char *)malloc(infologLength);
					glGetProgramInfoLog(pipelineID, infologLength, &charsWritten, infoLog);

					std::string log = infoLog;

					std::cerr << "Unable to link pipeline" << log;
					throw std::runtime_error("Pipeline cannot be linked");
				}
			}

			OGLPipeline::OGLPipeline(VertexShader & vs, FragmentShader & fs, GeometryShader & gs)
			{
				pipelineID = glCreateProgram();
				glAttachShader(pipelineID, vs.vertexID);
				glAttachShader(pipelineID, fs.fragmentID);
				glAttachShader(pipelineID, gs.geometryID);
				glLinkProgram(pipelineID);
				GLint programSuccess = GL_TRUE;
				glGetProgramiv(pipelineID, GL_LINK_STATUS, &programSuccess);

				if (programSuccess != GL_TRUE)
				{
					int infologLength = 0;

					int charsWritten = 0;
					char *infoLog;

					glGetProgramiv(pipelineID, GL_INFO_LOG_LENGTH, &infologLength);

					infoLog = (char *)malloc(infologLength);
					glGetProgramInfoLog(pipelineID, infologLength, &charsWritten, infoLog);

					std::string log = infoLog;

					std::cerr << "Unable to link pipeline" << log;
					throw std::runtime_error("Pipeline cannot be linked");
				}
			}

			OGLPipeline::~OGLPipeline()
			{
			}

			void OGLPipeline::run()
			{
				glUseProgram(pipelineID);
			}
			void OGLPipeline::stop()
			{
				glUseProgram(NULL);
			}
			bool OGLPipeline::createUniform(const char * name)
			{
				int uniColor = glGetUniformLocation(pipelineID, name);
				uniforms[name] = uniColor;
				return true;
			}
			bool OGLPipeline::setUniformMatrix4f(const char * name, glm::mat4 matrix)
			{
				int id = uniforms[name];
				glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(matrix));
				return true;
			}

			bool OGLPipeline::setUniformVector(const char * name, float x, float y, float z)
			{
				int id = uniforms[name];
				glUniform3f(id, x, y, z);
				return true;
			}

			bool OGLPipeline::setUniformInt(const char* name, int value)
			{
				int id = uniforms[name];
				glUniform1i(id, value);
				return true;
			}

			bool OGLPipeline::setUniformFloat(const char * name, float value)
			{
				int id = uniforms[name];
				glUniform1f(id, value);
				return true;
			}
		}
	}
}