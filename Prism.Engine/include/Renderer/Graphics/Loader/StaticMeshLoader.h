#pragma once

#include <string>
#include <memory>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/Models/Mesh.h"

namespace Renderer
{
	namespace Graphics
	{
		namespace Loader
		{
			class StaticMeshLoader
			{
			public:
				StaticMeshLoader();
				std::shared_ptr<Models::Mesh> loadMesh(std::string path);
				~StaticMeshLoader();
			private:
				RenderDevice* renderDevice;
			};
		}
	}
}
