#include <glm/glm.hpp>
#include "Renderer/Graphics/OpenGL/OGLVertexBuffer.h"
#include "Renderer/Graphics/VertexArrayObject.h"
#include "Renderer/Graphics/IndexBuffer.h"
#include "Renderer/Graphics/Models/Mesh.h"
#include <string>
#include <vector>
#include <memory>

using namespace std;

namespace Renderer
{
	namespace Graphics
	{
		namespace Models
		{
			Mesh::Mesh(unique_ptr<VertexArrayObject> vertexArrayObject, unique_ptr<IndexBuffer> indexBuffer)
			{
				this->vertexArrayObject = move(vertexArrayObject);
				this->indexBuffer = move(indexBuffer);
				isIndiced = true;
			}

			Mesh::Mesh(unique_ptr<VertexArrayObject> vertexArrayObject)
			{
				this->vertexArrayObject = move(vertexArrayObject);
			}
		}
	}
}
