#pragma once
#include <glm/glm.hpp>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/Loader/ModelLoader.h"
#include "Renderer/Graphics/Loader/StaticMeshLoader.h"
#include "Renderer/Graphics/Models/Model.h"
#include "Renderer/Graphics/Models/Mesh.h"
#include "Renderer/Graphics/IndexBuffer.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Renderer/Graphics/RenderDevice.h"
#include <vector>
#include <string>
#include <memory>
#include <map>

namespace Renderer {
	namespace Graphics {
		namespace Loader {
			class ModelLoader {
			public:
				std::unique_ptr<Renderer::Graphics::Models::Model> loadModel(std::string path) const;
			private:
				StaticMeshLoader staticMeshLoader;
			};
		}
	}
}