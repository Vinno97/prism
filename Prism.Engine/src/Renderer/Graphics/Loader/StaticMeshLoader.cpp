#pragma once

#include "Renderer/Graphics/Loader/StaticMeshLoader.h"
#include "Renderer/Graphics/Models/Mesh.h"
#include "Renderer/Graphics/RenderDevice.h"
#include <string>

using namespace std;
using namespace Renderer::Graphics::Models;

namespace Renderer {
	namespace Graphics {
		namespace Loader {
			StaticMeshLoader::StaticMeshLoader()
			{
			}


			Mesh* StaticMeshLoader::loadMesh(std::string path, RenderDevice* renderDevice)
			{
				return nullptr;
			}

			StaticMeshLoader::~StaticMeshLoader()
			{
			}
		}
	}
}