#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <string>
#include "RenderAPI/RenderDevice.h"
#include "RenderAPI/VertexShader.h"
#include "RenderAPI/VertexBuffer.h"
#include "RenderAPI/IndexBuffer.h"

namespace Renderer {
	class CoreRenderer
	{
	public:
		CoreRenderer();
		void init();
		void draw();
		~CoreRenderer();
	private:
		RenderAPI::RenderDevice* renderDevice;
		RenderAPI::VertexShader* vertexShader;
		RenderAPI::FragmentShader* fragmentShader;
		RenderAPI::Pipeline* pipeline;
		RenderAPI::VertexBuffer* vertexBuffer;
		RenderAPI::IndexBuffer* indexBuffer;

		GLuint gProgramID;
		GLuint gVertexPos2DLocation;
		GLuint gVBO;
		GLuint gIBO;
	};
}