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

		renderDevice = OGLRenderDevice::getRenderDevice();

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

	//TOD: Fix memory leak
	void Control::UpdateTexture(const char *path)
	{
		auto pwd = filesystem::current_path();
		auto filepath = pwd.concat("/res/").concat(path);

		if (!filesystem::exists(filepath)) {
			throw std::invalid_argument("File does not exist");
			return;
		}

		texture = renderDevice->createTexture(filepath.generic_string().c_str());
	}

	void Control::onClick()
	{
		if(callback != nullptr)
			callback();
	}
}