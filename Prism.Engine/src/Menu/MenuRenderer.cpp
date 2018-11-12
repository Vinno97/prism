#include "Menu/MenuRenderer.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/VertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"
#include "Renderer/Graphics/VertexArrayObject.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Util/FileReader.h"

using namespace std;
using namespace Renderer;
using namespace Renderer::Graphics;
using namespace Renderer::Graphics::OpenGL;

namespace Menu {
	MenuRenderer::MenuRenderer()
	{
		renderDevice = OGLRenderDevice::getRenderDevice();
		Util::FileReader fileReader;
		string vertexSource = fileReader.readResourceFileIntoString("/shaders/menuShader.vs");
		string fragmentSource = fileReader.readResourceFileIntoString("/shaders/menuShader.fs");

		std::unique_ptr<VertexShader> vertexShader = renderDevice->createVertexShader(vertexSource.c_str());
		std::unique_ptr<FragmentShader> fragmentShader = renderDevice->createFragmentShader(fragmentSource.c_str());
		menuPipeline = move(renderDevice->createPipeline(*vertexShader, *fragmentShader));
	}
	void MenuRenderer::renderMenu(Menu& menu)
	{
		menuPipeline->run();
		for (auto& control : menu.controls) {
			control.model.mesh->vertexArrayObject->bind();
			renderDevice->DrawTriangles(0, control.model.mesh->verticesLength);
		}
		menuPipeline->stop();
	}
}