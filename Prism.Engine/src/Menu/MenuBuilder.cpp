#include <iostream>
#include <sstream>

#include "Menu/MenuBuilder.h"
#include "Renderer/Renderable.h"
#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "Renderer/Graphics/Models/Model.h"
#include "Renderer/Graphics/Models/Mesh.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/Models/Mesh.h"
#include "Renderer/Graphics/RenderDevice.h"
#include "Surface.h"

using namespace std;
using namespace Renderer::Graphics;
using namespace Renderer::Graphics::OpenGL;
using namespace Renderer::Graphics::Models;

namespace Menu {
	MenuBuilder::MenuBuilder()
	{
		menu = Menu{};
		renderDevice = OGLRenderDevice::getRenderDevice();
		this->initMesh();
	}

	//Create a single mesh so we can reuse it
	void MenuBuilder::initMesh() {
		float* verticesArray = vertices;
		unsigned int* indicesArray = indices;

		auto verticesSize = 8 * sizeof(float);

		unique_ptr<VertexBuffer> vertexBuffer = renderDevice->createVertexBuffer(verticesSize, verticesArray);

		std::unique_ptr<VertexArrayObject> vertexArrayObject = renderDevice->createVertexArrayobject();
		vertexArrayObject->addVertexBuffer(move(vertexBuffer), 0, 2 * sizeof(float), 0, 2);
		unique_ptr<IndexBuffer> indexBuffer = renderDevice->createIndexBuffer(6 * sizeof(unsigned int), indicesArray);

		mesh = make_shared<Mesh>(move(vertexArrayObject), move(indexBuffer));
		mesh->isIndiced = true;
		mesh->indicesLength = 6;

		menu.mesh = mesh;
	}

	void MenuBuilder::addControl(float x, float y, float width, float height, const char *path)
	{
		Control control{x, y, width, height, path };
		Model model = Model{ mesh };

		menu.controls.push_back(control);
	}

	Menu MenuBuilder::buildMenu()
	{
		return menu;
	}
}


