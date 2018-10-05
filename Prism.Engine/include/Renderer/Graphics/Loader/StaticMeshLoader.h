#pragma once

#include <string>
#include "Renderer/Graphics/RenderDevice.h"

namespace Renderer {
	namespace Graphics {
		namespace Loader {
			class StaticMeshLoader {
			public:
				StaticMeshLoader();

				void loadMesh();

				~StaticMeshLoader();
			};
		}
	}
}