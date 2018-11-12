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

				std::shared_ptr<Mesh> loadMesh(string path);

				~StaticMeshLoader();

			private:
				RenderDevice* renderDevice;
			};
		}
	}
}