#pragma once

#include "Renderer/Graphics/VertexArrayObject.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/Models/Model.h"
#include "Math/Vector3f.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <functional>

namespace Menu
{
	class Control
	{
	public:
		Control() = default;
		Control(float x, float y, float width, float height, const char* path);
		Control(float x, float y, float width, float height, const char* path, std::function<void()> callback_);
		void UpdateTexture(const char* path);
		void onClick();

		Math::Vector3f position;
		Math::Vector3f size;
		float rotation = 0;
		std::shared_ptr<Renderer::Graphics::Texture> texture;

		std::function<void()> callback;
	};
}
