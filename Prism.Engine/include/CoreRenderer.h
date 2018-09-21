#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <string>
#include "RenderFacade/RenderDevice.h"
#include "RenderFacade/VertexShader.h"
#include "RenderFacade/VertexBuffer.h"
#include "RenderFacade/IndexBuffer.h"

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
		RenderFacade::VertexBuffer* vertexBuffer;
		RenderFacade::IndexBuffer* indexBuffer;

		GLuint gProgramID;
		GLuint gVertexPos2DLocation;
		GLuint gVBO;
		GLuint gIBO;
	};
}