#pragma once
#include <glm/glm.hpp>
#include "Renderer/Graphics/VertexArrayObject.h"
#include "Renderer/Graphics/IndexBuffer.h"
#include "Renderer/Graphics/Models/Mesh.h"
#include "Renderer/Graphics/Models/Material.h"
#include "Renderer/Graphics/Texture.h"
#include <memory>

namespace Renderer {
	namespace Graphics {
		namespace Models {
			class Model {
				public: 
					Model() = default;
					std::shared_ptr<Mesh> mesh;
					Model(const Model &other);
					Model& operator=(const Model& other);
					Model(Model&& other);
					Model& operator=(Model&& other);

					Model(std::shared_ptr<Mesh> m);
					std::shared_ptr<Texture> texture;
				};
		}
	}
}