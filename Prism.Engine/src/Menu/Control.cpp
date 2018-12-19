#include "Menu/Control.h"
#include <vector>
#include <memory>
#include "Renderer/Graphics/Models/Model.h"
#include "Renderer/Graphics/Models/Mesh.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/Models/Mesh.h"
#include "Renderer/Graphics/RenderDevice.h"
#include "Surface.h"
#include <stdexcept>

#ifdef _MSC_VER
	#include <filesystem>
#else
	#include <experimental/filesystem>
#endif

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

using namespace std;
using namespace std::experimental;
using namespace Renderer::Graphics;
using namespace Renderer::Graphics::OpenGL;
using namespace Renderer::Graphics::Models;

namespace Menu {
	Control::Control(float x, float y, float width, float height, const char *path)
	{
		position = Math::Vector3f{ x, y, 0 };
		size = Math::Vector3f{width, height, 0};

		RenderDevice* renderDevice = OGLRenderDevice::getRenderDevice();

		auto pwd = filesystem::current_path();
		auto filepath = pwd.concat("/res/").concat(path);

		if (!filesystem::exists(filepath)) {
			throw std::invalid_argument("File does not exist");
			return;
		}

		texture = renderDevice->createTexture(filepath.generic_string().c_str());
	}

	Control::Control(float x, float y, float width, float height, const char * path, std::function<void()> callback_) : Control(x, y, width, height, path)
	{
		callback = callback_;
	}

	Control::Control(float x, float y, float width, float height, const char * path,
		std::function<void(Control* control, Context& context)> hoverCallback_,
		std::function<void(Control* control, Context& context)> leaveCallback_) : Control(x, y, width, height, path)
	{
		leaveCallback = leaveCallback_;
		hoverCallback = hoverCallback_;
	}

	Control::Control(float x, float y, float width, float height, const char * path, 
		std::function<void()> callback_, 
		std::function<void(Control* control, Context& context)> hoverCallback_,
		std::function<void(Control* control, Context& context)> leaveCallback_) : Control(x, y, width, height, path)
	{
		callback = callback_;
		leaveCallback = leaveCallback_;
		hoverCallback = hoverCallback_;
	}

	void Control::UpdateTexture(const char *path)
	{

	}

	void Control::onClick()
	{
		if(callback != nullptr)
			callback();
	}
	void Control::onEnter(Context& context)
	{
		if (hoverCallback == nullptr || isActive)
			return;

		hoverCallback(this, context);
		isActive = true;
	}

	void Control::onLeave(Context& context)
	{
		if (leaveCallback == nullptr || !isActive)
			return;

		leaveCallback(this, context);
		isActive = false;
	}
}