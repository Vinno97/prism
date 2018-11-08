#pragma once
#include <glm/glm.hpp>
#include "Renderer/Graphics/Models/Model.h"
#include "Renderer/Graphics/Models/Mesh.h"
#include <memory>

using namespace std;

namespace Renderer {
	namespace Graphics {
		namespace Models {
			Model::Model(shared_ptr<Mesh> m) : mesh{ m } { }
		}
		
	}
}