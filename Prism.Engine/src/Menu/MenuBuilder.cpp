#include "Menu/MenuBuilder.h"
#include "Renderer/Renderable.h"
#include <vector>
#include <memory>
#include "Renderer/Graphics/Models/Model.h"
#include "Renderer/Graphics/Models/Mesh.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/RenderDevice.h"

using namespace std;
using namespace Renderer::Graphics;
using namespace Renderer::Graphics::OpenGL;
using namespace Renderer::Graphics::Models;

namespace Menu {
	MenuBuilder::MenuBuilder() {
		menu = std::make_unique<Menu>();

		renderDevice = OGLRenderDevice::getRenderDevice();
		this->initMesh();
	}

	TextControl* MenuBuilder::addTextControl(float x, float y, float scale, Math::Vector3f colour, std::string text)
	{
		std::unique_ptr<TextControl> textControl = std::make_unique<TextControl>(text);
		textControl->position.x = x;
		textControl->position.y = y;
		textControl->colour = colour;
		textControl->scale = scale;
		menu->textControls.push_back(std::move(textControl));

		return menu->textControls[menu->textControls.size() - 1].get();
	}

	//Create a single mesh so we can reuse it
	void MenuBuilder::initMesh() {
		float* verticesArray = vertices;
		unsigned int* indicesArray = indices;

		auto verticesSize = 8 * sizeof(float);

		unique_ptr<VertexBuffer> vertexBuffer = renderDevice->createVertexBuffer(verticesSize, verticesArray);

		std::unique_ptr<VertexArrayObject> vertexArrayObject = renderDevice->createVertexArrayobject();
		std::unique_ptr<VertexBuffer> texBuffer = renderDevice->createVertexBuffer(verticesSize, texCoords);

		vertexArrayObject->addVertexBuffer(vertexBuffer.get(), 0, 2 * sizeof(float), 0, 2);
		vertexArrayObject->addVertexBuffer(texBuffer.get(), 1, 2 * sizeof(float), 0, 2);

		unique_ptr<IndexBuffer> indexBuffer = renderDevice->createIndexBuffer(6 * sizeof(unsigned int), indicesArray);

		mesh = make_shared<Mesh>(move(vertexArrayObject), move(indexBuffer));
		mesh->isIndiced = true;
		mesh->indicesLength = 6;

		menu->mesh = mesh;
	}

	void MenuBuilder::addControl(float x, float y, float width, float height, const char *path)
	{
		std::unique_ptr<Control> control = std::make_unique<Control>(x, y, width, height, path);
		Model model = Model{ mesh };

		control->hoverCallback = hoverCallback;
		control->leaveCallback = leaveCallback;

		menu->controls.push_back(std::move(control));
	}

	Control* MenuBuilder::addImage(float x, float y, float width, float height, const char *path) {
		std::unique_ptr<Control> control = std::make_unique<Control>(x, y, width, height, path);
		Model model = Model{ mesh };
		menu->controls.push_back(std::move(control));

		return menu->controls[menu->controls.size() - 1].get();
	}

	void MenuBuilder::addControl(float x, float y, float width, float height, const char * path, std::function<void()> callback_)
	{
		std::unique_ptr<Control> control = std::make_unique<Control>(x, y, width, height, path, callback_);
		Model model = Model{ mesh };
		control->hoverCallback = hoverCallback;
		control->leaveCallback = leaveCallback;
		menu->controls.push_back(std::move(control));
	}

	void MenuBuilder::addControl(float x, float y, float width, float height, const char * path, 
		std::function<void(Control* control, Context& context)> hoverCallback_, 
		std::function<void(Control* control, Context& context)> leaveCallback_)
	{
		std::unique_ptr<Control> control = std::make_unique<Control>( x, y, width, height, path, hoverCallback_, leaveCallback_ );
		Model model = Model{ mesh };
		menu->controls.push_back(std::move(control));
	}

	void MenuBuilder::addControl(float x, float y, float width, float height, const char * path, 
		std::function<void()> callback_, 
		std::function<void(Control* control, Context& context)> hoverCallback_,
		std::function<void(Control* control, Context& context)> leaveCallback_)
	{
		std::unique_ptr<Control> control = std::make_unique<Control>( x, y, width, height, path, callback_, hoverCallback_, leaveCallback_ );
		Model model = Model{ mesh };
		menu->controls.push_back(std::move(control));
	}

    std::unique_ptr<Menu> MenuBuilder::buildMenu()
	{
		return std::move(menu);
	}
}


