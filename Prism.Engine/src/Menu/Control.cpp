#include "Menu/Control.h"
#include <vector>
#include <memory>
#include "Renderer/Graphics/Models/Model.h"
#include "Renderer/Graphics/Models/Mesh.h"

using namespace std;
using namespace Renderer::Graphics;
using namespace Renderer::Graphics::OpenGL;
using namespace Renderer::Graphics::Models;

namespace Menu {
	Control::Control(int x, int y, int width, int height)
	{
		RenderDevice* renderDevice = OGLRenderDevice::getRenderDevice();

		std::vector<float> vertices;
		vertices.push_back(-0.5f);
		vertices.push_back(-0.5f);
		vertices.push_back(0.5f);
		vertices.push_back(-0.5f);
		vertices.push_back(0.f);
		vertices.push_back(0.5f);

		float* verticesArray = vertices.data();

		auto verticesSize = vertices.size() * sizeof(float);

		unique_ptr<VertexBuffer> vertexBuffer = renderDevice->createVertexBuffer(verticesSize, verticesArray);

		std::unique_ptr<Renderer::Graphics::VertexArrayObject> vertexArrayObject = renderDevice->createVertexArrayobject();
		vertexArrayObject->addVertexBuffer(move(vertexBuffer), 0, 3 * sizeof(float), 0, 3);
		Mesh mesh;
	}
}