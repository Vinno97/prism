#pragma once
#include "Renderer/Graphics/VertexArrayObject.h"
#include "Renderer/Graphics/IndexBuffer.h"
#include <memory>

namespace Renderer {
	namespace Graphics {
		namespace Models {
			class Mesh {
			public:
				Mesh(std::unique_ptr<VertexArrayObject> vertexArrayObject, std::unique_ptr<IndexBuffer> indexBuffer);
				Mesh(std::unique_ptr<VertexArrayObject> vertexArrayObject);

				std::unique_ptr<VertexArrayObject> vertexArrayObject;
				std::unique_ptr<IndexBuffer> indexBuffer;
				int indicesLength;
				int verticesLength;
				bool isIndiced = false;
			};
		}
	}
}