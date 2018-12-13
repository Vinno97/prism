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
#include <functional>

using namespace std;
using namespace Renderer;
using namespace Graphics;
using namespace OpenGL;

namespace Menu
{
	MenuRenderer::MenuRenderer()
	{
		renderDevice = OGLRenderDevice::getRenderDevice();
		Util::FileSystem fileReader;
		string vertexSource = fileReader.readResourceFileIntoString("/shaders/menuShader.vs");
		string fragmentSource = fileReader.readResourceFileIntoString("/shaders/menuShader.fs");

		std::unique_ptr<VertexShader> vertexShader = renderDevice->createVertexShader(vertexSource.c_str());
		std::unique_ptr<FragmentShader> fragmentShader = renderDevice->createFragmentShader(fragmentSource.c_str());
		menuPipeline = move(renderDevice->createPipeline(*vertexShader, *fragmentShader));

		menuPipeline->createUniform("model");
	}

	void MenuRenderer::renderMenu(Menu& menu, float aspect)
	{
		menuPipeline->run();
		renderDevice->useDepthTest(false);
		renderDevice->useBlending(true);

		menu.mesh->vertexArrayObject->bind();
		menu.mesh->indexBuffer->bind();

		for (auto& control : menu.controls)
		{
			auto pos = control.position;
			glm::mat4 model = glm::mat4(1.0f);

			model = translate(model, glm::vec3(pos.x, pos.y, 0.0f));
			model = glm::rotate(model, control.rotation, glm::vec3(0.f, 0.f, 1.f));
			model = scale(model, glm::vec3(control.size.x, control.size.y, 1.0f));

			menuPipeline->setUniformMatrix4f("model", model);

			control.texture->bind(textures[0]);
			renderDevice->DrawTrianglesIndexed(0, menu.mesh->indicesLength);
		}
		renderDevice->useBlending(false);
		menu.mesh->vertexArrayObject->unbind();

		glDisable(GL_BLEND);
		menuPipeline->stop();
		renderDevice->useDepthTest(true);

		for (auto& control : menu.textControls)
		{
			textRenderer.RenderText(*control);
		}
	}
}
