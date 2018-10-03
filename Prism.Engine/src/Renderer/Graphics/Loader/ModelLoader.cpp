#pragma once
#include <glm/glm.hpp>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/Loader/ModelLoader.h"
#include "Renderer/Graphics/Models/Model.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/IndexBuffer.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>

using namespace std;
using namespace Renderer::Graphics;
using namespace Renderer::Graphics::Models;
using namespace Renderer::Graphics::OpenGL;
using namespace Renderer::Graphics::Loader;


namespace Renderer {
	namespace Graphics {
		namespace Loader {

			Model ModelLoader::loadModel(string path)
			{
				RenderDevice* renderDevice = &OGLRenderDevice();

				Assimp::Importer importer;
				const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

				aiMesh* mesh = scene->mMeshes[0];
				VertexArrayObject* vertexArrayObject = renderDevice->createVertexArrayobject();
				VertexBuffer* vertexBuffer = renderDevice->createVertexBuffer(sizeof(mesh->mVertices), mesh->mVertices);

				vertexArrayObject->addVertexBuffer(vertexBuffer, 0, 3 * sizeof(float), 0, 3);

				vector<float>* indices = new vector<float>();
				for (unsigned int a = 0; a < sizeof(mesh->mFaces); a = a + 1)
				{
					aiFace temp = mesh->mFaces[a];
					for (unsigned int b = 0; b < sizeof(temp.mIndices); b = b + 1)
					{
						unsigned int temp2 = temp.mIndices[b];
						indices->push_back(temp2);
					}
				}

				float *indicesArray = indices->data();
				
				IndexBuffer* indexBuffer = renderDevice->createIndexBuffer(sizeof(indicesArray), indicesArray);

				vertexArrayObject->unbind();

				Mesh* m = new Mesh(vertexArrayObject, indexBuffer);

				return Model(*m);
			}

		}
	}
}