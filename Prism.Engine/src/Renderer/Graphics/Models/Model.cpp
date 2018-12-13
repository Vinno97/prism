#include <glm/glm.hpp>
#include "Renderer/Graphics/Models/Model.h"
#include "Renderer/Graphics/Models/Mesh.h"
#include <memory>

using namespace std;

namespace Renderer
{
	namespace Graphics
	{
		namespace Models
		{
			Model::Model(shared_ptr<Mesh> m) : mesh{m}
			{
			}

			Model::Model(const Model& other)
			{
				mesh = other.mesh;
				texture = other.texture;
			}

			Model& Model::operator=(const Model& other)
			{
				if (this != &other)
				{
					mesh = other.mesh;
					texture = other.texture;
				}
				return *this;
			}

			Model::Model(Model&& other)
			{
				mesh.swap(other.mesh);
				texture.swap(other.texture);
				other.mesh = nullptr;
				other.texture = nullptr;
			}

			Model& Model::operator=(Model&& other)
			{
				if (this != &other)
				{
					mesh.swap(other.mesh);
					texture.swap(other.texture);
				}
				return *this;
			}
		}
	}
}
