#include "Menu/TextControl.h"
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
	TextControl::TextControl(float x, float y, float width, float height, std::string text) : text{ text }
	{
		position = Math::Vector3f{ x, y, 0 };
		size = Math::Vector3f{ width, height, 0 };

		RenderDevice* renderDevice = OGLRenderDevice::getRenderDevice();
	}
}