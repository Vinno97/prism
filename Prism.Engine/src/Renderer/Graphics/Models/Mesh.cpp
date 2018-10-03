#pragma once
#include <glm/glm.hpp>
#include "Renderer/Graphics/OpenGL/OGLVertexBuffer.h"
#include "Renderer/Graphics/VertexArrayObject.h"
#include "Renderer/Graphics/IndexBuffer.h"
#include "Renderer/Graphics/Models/Mesh.h"
#include <string>
#include <vector>

using namespace std;

namespace Renderer {
	namespace Graphics {
		namespace Models {
			Mesh::Mesh()
			{
			}
			Mesh::Mesh(VertexArrayObject* vertexArrayObject, IndexBuffer* indexBuffer) {
				this->vertexArrayObject = vertexArrayObject;
				this->indexBuffer = indexBuffer;
			}

			VertexArrayObject* vertexArrayObject;
			IndexBuffer* indexBuffer;

		}
	}
}