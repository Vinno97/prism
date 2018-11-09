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

			Model::Model(const Model & other)
			{
				mesh = other.mesh;
			}

			Model & Model::operator=(const Model & other)
			{
				if (this != &other) {
					mesh = other.mesh;
				}
				return *this;
			}

			Model::Model(Model && other)
			{
				mesh.swap(other.mesh);
				other.mesh = nullptr;
			}

			Model & Model::operator=(Model && other)
			{
				if (this != &other) {
					mesh.swap(other.mesh);
				}
				return *this;
			}
		}
		
	}
}