#pragma once
#include <glm/glm.hpp>
#include "Renderer/Graphics/OpenGL/OGLVertexBuffer.h"
#include <string>

namespace Renderer {
	namespace Graphics {
		namespace Models {
			class Mesh;

			struct Vertex {
				glm::vec3 Position;
				glm::vec3 Normal;
				glm::vec2 TexCoords;
			};

			struct Texture {
				unsigned int id;
				std::string type;
			};

			class Mesh {
				public:
					//VertexBuffer vertices;
				private:

			};
		}
	}
}