#pragma once
#include <gl\glew.h>
#include <SDL2/SDL_opengl.h>
#include "RenderFacade/OGLVertexShader.h"
#include <iostream> 
namespace RenderFacade {
		OGLVertexShader::OGLVertexShader(const char* source) {
			// ------------------------------------
			// vertex shader
			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &source, NULL);
			glCompileShader(vertexShader);

	//		// check for shader compile errors
			int success;
			char infoLog[512];
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
			if(!success)
			{
				glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			}
		}
	};
