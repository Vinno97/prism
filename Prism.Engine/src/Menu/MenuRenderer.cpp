#include "Menu/MenuRenderer.h"
#include <string>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/VertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"
#include "Renderer/Graphics/VertexArrayObject.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Util/FileSystem.h"
#include <SDL2/SDL_opengl.h>

#include <random>
#include <functional>

using namespace std;
using namespace Renderer;
using namespace Renderer::Graphics;
using namespace Renderer::Graphics::OpenGL;

namespace Menu {
	MenuRenderer::MenuRenderer()
	{
		renderDevice = OGLRenderDevice::getRenderDevice();
		Util::FileSystem fileReader;
		string vertexSource = fileReader.readResourceFileIntoString("/shaders/menuShader.vs");
		string fragmentSource = fileReader.readResourceFileIntoString("/shaders/menuShader.fs");

		std::unique_ptr<VertexShader> vertexShader = renderDevice->createVertexShader(vertexSource.c_str());
		std::unique_ptr<FragmentShader> fragmentShader = renderDevice->createFragmentShader(fragmentSource.c_str());
		menuPipeline = move(renderDevice->createPipeline(*vertexShader, *fragmentShader));

		menuPipeline->createUniform("view");
		menuPipeline->createUniform("model");
			
		float width = 1080 / 2;
		float height = 1920 / 2;

		float aspect = float(1920/2)/float(1080/2);

		projection = glm::ortho(-aspect, aspect, -1.f, 1.f, -1.0f, 1.0f);
	}
	void MenuRenderer::renderMenu(Menu& menu)
	{
		menuPipeline->run();
		menuPipeline->setUniformMatrix4f("view", projection);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		float aspect = float(1920) / float(1080);

		menu.mesh->vertexArrayObject->bind();
		menu.mesh->indexBuffer->bind();

		for (auto& control : menu.controls) 
		{
			auto pos = control.position;
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(pos.x, pos.y, 0.0f));
			model = glm::scale(model, glm::vec3(control.size.x, control.size.y*aspect, 1.0f));

			menuPipeline->setUniformMatrix4f("model", model);

			control.texture->bind();
			renderDevice->DrawTrianglesIndexed(0, menu.mesh->indicesLength);	
		}
		menu.mesh->vertexArrayObject->unbind();

		glDisable(GL_BLEND);
		menuPipeline->stop();
	}
}