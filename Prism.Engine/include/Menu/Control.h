#pragma once

#include "Renderer/Graphics/VertexArrayObject.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/Models/Model.h"
#include "Math/Vector3f.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

namespace Menu {
	class Control
	{
	public:
		Control() = default;
		Control(float x, float y, float width, float height, SDL_Window *window);
		SDL_Window *window;
		SDL_Texture* texture;
		SDL_Renderer *renderer;
		void DrawTexture();
		void UpdateTexture(const char *path);
		SDL_Texture* Surface;
		Renderer::Graphics::Models::Model model;
		Math::Vector3f position;
		Math::Vector3f size;
	};
}
