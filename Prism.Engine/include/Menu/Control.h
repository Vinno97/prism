#pragma once

#include "Context.h"
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
			std::function<void(Control* control, Context& context)> hoverCallback_,
			std::function<void(Control* control, Context& context)> leaveCallback_);
		Control(float x, float y, float width, float height, const char *path, 
			std::function<void()> callback_, 
			std::function<void(Control* control, Context& context)> hoverCallback_,
			std::function<void(Control* control, Context& context)> leaveCallback_);
		void UpdateTexture(const char *path);
		void onClick();
		void onEnter(Context& context);
		void onLeave(Context& context);

		Math::Vector3f position;
		Math::Vector3f size;
		Math::Vector3f offset{0.f, 0.f, 0.f};
		float rotation = 0;
		std::shared_ptr<Renderer::Graphics::Texture> texture;

		std::function<void(Control* control, Context& context)> hoverCallback;
		std::function<void(Control* control, Context& context)> leaveCallback;
		std::function<void()> callback;

		bool isActive = false;
	private:
	};
}
