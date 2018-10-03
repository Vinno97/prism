#pragma once
#include <glm/glm.hpp>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/IndexBuffer.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Renderer/Graphics/Loader/ModelLoader.h"
#include "Renderer/Graphics/Models/Model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace Renderer::Graphics;
using namespace Renderer::Graphics::OpenGL;
using namespace Renderer::Graphics::Models;

namespace Renderer {
	namespace Graphics {
		namespace Loader {
			ModelLoader::ModelLoader(RenderDevice * renderDevice)
			{
				this->renderDevice = renderDevice;
			}
			Model* ModelLoader::loadModel(string path)
			{
				Assimp::Importer importer;
				const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

				if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
				{
					auto error = importer.GetErrorString();
					cout << "ERROR::ASSIMP::" << error << endl;
					throw exception("a");
				}

				aiMesh* mesh = scene->mMeshes[0];

				vector<float>* vertices = new vector<float>();

				for (unsigned int a = 0; a < mesh->mNumVertices; a = a + 1) {
					auto v = mesh->mVertices[a];
					vertices->push_back(v.x);
					vertices->push_back(v.y);
					vertices->push_back(v.z);
				}

				float *verticesArray = vertices->data();

				VertexArrayObject* vertexArrayObject = renderDevice->createVertexArrayobject();

				auto test = vertices->size() * sizeof(float);

				VertexBuffer* vertexBuffer = renderDevice->createVertexBuffer(test, verticesArray);

				vertexArrayObject->addVertexBuffer(vertexBuffer, 0, 3 * sizeof(float), 0, 3);

				vector<int>* indices = new vector<int>();
				for (unsigned int a = 0; a < mesh->mNumFaces; a = a + 1)
				{
					aiFace temp = mesh->mFaces[a];
					for (unsigned int b = 0; b < temp.mNumIndices; b = b + 1)
					{
						unsigned int temp2 = temp.mIndices[b];
						indices->push_back(temp2);
					}
				}
				
				int *indicesArray = indices->data();
				
				IndexBuffer* indexBuffer = renderDevice->createIndexBuffer(indices->size()*sizeof(unsigned int), indicesArray);

				vertexArrayObject->unbind();

				Mesh* m = new Mesh(vertexArrayObject, indexBuffer);
				m->indicesLength = indices->size();

				return new Model(m);
			}
		}
	}
}