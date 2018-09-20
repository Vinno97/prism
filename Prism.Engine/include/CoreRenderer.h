#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <string>
#include "RenderFacade/RenderDevice.h"
#include "RenderFacade/VertexShader.h"

namespace Renderer {
	class CoreRenderer
	{
	public:
		CoreRenderer();
		void init();
		void draw();
		~CoreRenderer();
	private:
		RenderFacade::RenderDevice* renderDevice;
		RenderFacade::VertexShader* vertexShader;
		RenderFacade::FragmentShader* fragmentShader;
		RenderFacade::Pipeline* pipeline;

		GLuint gProgramID;
		GLuint gVertexPos2DLocation;
		GLuint gVBO;
		GLuint gIBO;
	};
}