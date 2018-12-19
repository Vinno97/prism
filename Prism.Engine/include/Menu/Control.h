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

namespace Menu {
	class Control
	{
	public:

		Control(float x, float y, float width, float height, const char *path);
		Control(float x, float y, float width, float height, const char *path, std::function<void()> callback_);
		Control(float x, float y, float width, float height, const char *path,
			std::function<void(Math::Vector3f& position, Math::Vector3f& size)> hoverCallback_,
			std::function<void(Math::Vector3f& position, Math::Vector3f& size)> leaveCallback_);
		Control(float x, float y, float width, float height, const char *path, 
			std::function<void()> callback_, 
			std::function<void(Math::Vector3f& position, Math::Vector3f& size)> hoverCallback_, 
			std::function<void(Math::Vector3f& position, Math::Vector3f& size)> leaveCallback_);
		void UpdateTexture(const char *path);
		void onClick();
		void onEnter();
		void onLeave();

		Math::Vector3f position;
		Math::Vector3f size;
		float rotation = 0;
		std::shared_ptr<Renderer::Graphics::Texture> texture;

		std::function<void(Math::Vector3f& position, Math::Vector3f& size)> hoverCallback;
		std::function<void(Math::Vector3f& position, Math::Vector3f& size)> leaveCallback;
		std::function<void()> callback;

		bool isActive = false;
	private:
	};
}
