#pragma once

#include <memory>
#include <functional>
#include <string>
#include "Menu/Menu.h"
#include "Menu/TextControl.h"
#include "Renderer/Graphics/Models/Model.h"
#include "Renderer/Graphics/Models/Mesh.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/RenderDevice.h"

namespace Menu {
	class MenuBuilder
	{
	public:
		MenuBuilder();
		TextControl& addTextControl(float x, float y, float scale, Math::Vector3f colour, std::string text);
		void addControl(float x, float y, float width, float height, const char *path);
		void addControl(float x, float y, float width, float height, const char *path, std::function<void()> callback_);
		std::unique_ptr<Menu> buildMenu();
	private:
		void initMesh();

		Renderer::Graphics::RenderDevice* renderDevice;
		std::shared_ptr<Renderer::Graphics::Models::Mesh> mesh;
		std::unique_ptr<Menu> menu;

		float vertices[8] = {
			 1.0f,  1.0f,  // top right
			 1.0f,  0.0f,  // bottom right
			 0.0f,  0.0f,  // bottom left
			 0.0f,  1.0f   // top left 
		};

		float texCoords[8] = {
			1.0f,  0.0f,
			1.0f,  1.0f,
			0.0f,  1.0f,
			0.0f,  0.0f,
		};

		unsigned int indices[6] = {
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};
	};
}