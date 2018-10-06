#pragma once

#include <string>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/Models/Mesh.h"

using namespace Renderer::Graphics::Models;

namespace Renderer {
	namespace Graphics {
		namespace Loader {
			class StaticMeshLoader {
			public:
				StaticMeshLoader();

				Mesh* loadMesh(std::string path, RenderDevice* renderDevice);

				~StaticMeshLoader();
			};
		}
	}
}