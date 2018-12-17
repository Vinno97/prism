#pragma once

#include <string>
#include <memory>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/Models/Mesh.h"

namespace Renderer {
	namespace Graphics {
		namespace Loader {
			class StaticMeshLoader {
			public:
				StaticMeshLoader();
				std::shared_ptr<Renderer::Graphics::Models::Mesh> loadMesh(std::string path) const;
				~StaticMeshLoader();
			private:
				RenderDevice* renderDevice;
				// The cache can be mutable, since it does not affect the logical state of StaticMeshLoader.
				mutable std::map<std::string, std::shared_ptr<Models::Mesh>> loadedMeshes;
			};
		}
	}
}