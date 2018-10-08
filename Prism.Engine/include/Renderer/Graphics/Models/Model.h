#pragma once
#include <glm/glm.hpp>
#include "Renderer/Graphics/VertexArrayObject.h"
#include "Renderer/Graphics/IndexBuffer.h"
#include "Renderer/Graphics/Models/Mesh.h"
#include "Renderer/Graphics/Models/Material.h"
#include <memory>

using namespace std;

namespace Renderer {
	namespace Graphics {
		namespace Models {

			class Model {
				public: 
					Model(std::unique_ptr<Mesh> m);
					std::unique_ptr<Mesh> mesh;
					//Material material;
				};
		}
	}
}