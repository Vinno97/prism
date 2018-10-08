#pragma once

#include <string>
#include <memory>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/Models/Mesh.h"

using namespace Renderer::Graphics::Models;

namespace Renderer {
	namespace Graphics {
		namespace Loader {
			class StaticMeshLoader {
			public:
				StaticMeshLoader();

				std::unique_ptr<Mesh> loadMesh(std::string path, RenderDevice* renderDevice);

				~StaticMeshLoader();
			};
		}
	}
}