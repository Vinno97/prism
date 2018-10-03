#pragma once
#include <glm/glm.hpp>
#include "Renderer/Graphics/VertexArrayObject.h"
#include "Renderer/Graphics/IndexBuffer.h"


using namespace std;

namespace Renderer {
	namespace Graphics {
		namespace Models {

			class Mesh {
				public:
					Mesh();
					Mesh(VertexArrayObject* vertexArrayObject, IndexBuffer* indexBuffer);
					VertexArrayObject* vertexArrayObject;
					IndexBuffer* indexBuffer;

				private:


			};
		}
	}
}