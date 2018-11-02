#pragma once
#include "Renderer/Graphics/VertexArrayObject.h"
#include "Renderer/Graphics/IndexBuffer.h"
#include <memory>

using namespace std;

namespace Renderer {
	namespace Graphics {
		namespace Models {
			class Mesh {
			public:
				Mesh(unique_ptr<VertexArrayObject> vertexArrayObject, unique_ptr<IndexBuffer> indexBuffer);

				unique_ptr<VertexArrayObject> vertexArrayObject;
				unique_ptr<IndexBuffer> indexBuffer;
				int indicesLength;
			};
		}
	}
}