#pragma once
#include <glm/glm.hpp>
#include "Renderer/Graphics/Models/Model.h"
#include "Renderer/Graphics/Models/Mesh.h"

using namespace std;

namespace Renderer {
	namespace Graphics {
		namespace Models {
			Model::Model(Mesh* m) {
				this->mesh = m;
			}
		}
		
	}
}