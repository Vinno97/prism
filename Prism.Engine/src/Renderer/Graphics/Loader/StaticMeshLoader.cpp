#pragma once

#include "Renderer/Graphics/Loader/StaticMeshLoader.h"
#include "Renderer/Graphics/Models/Mesh.h"
#include "Renderer/Graphics/RenderDevice.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <vector>
#include <array>

using namespace std;
using namespace Renderer::Graphics::Models;

namespace Renderer {
	namespace Graphics {
		namespace Loader {
			StaticMeshLoader::StaticMeshLoader()
			{
			}

			/// <summary>
			/// Load a mesh
			/// </summary>
			/// <param name="path">The file path</param>
			/// <param name="renderDevice">The RenderDevice</param>
			/// <returns>Mesh*</returns>
			Mesh* StaticMeshLoader::loadMesh(std::string path, RenderDevice* renderDevice)
			{
				Assimp::Importer importer;

				// Import scene pointer from given path.
				const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

				if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
				{
					auto error = importer.GetErrorString();

					cout << "ERROR::ASSIMP::" << error << endl;
					throw exception("Assimp mesh loading.");
				}

				// Get the first mesh of the scene.  
				// Needs function to handle all meshes from the scene.
				aiMesh* mesh = scene->mMeshes[0];

				vector<float> vertices;

				//Scene is empty.
				if (!mesh)
				{
					cout << "Scene does not contain any meshes." << endl;
					throw exception("Assimp mesh loading.");
				}

				// iterate over the mesh's vertices and push the 3d coordinates into the vector.
				for (unsigned int a = 0; a < mesh->mNumVertices; a = a + 1) {
					auto v = mesh->mVertices[a];
					vertices.push_back(v.x);
					vertices.push_back(v.y);
					vertices.push_back(v.z);
				}

				// Convert vector to array.
				float* verticesArray = vertices.data();

				VertexArrayObject* vertexArrayObject = renderDevice->createVertexArrayobject();


				if (!vertexArrayObject)
				{
					cout << "Failed to create VAO." << endl;
					throw exception("Assimp mesh loading.");
				}

				// Get the size of the vertices to provide the VertexBuffer with the right data.
				auto verticesSize = vertices.size() * sizeof(float);

				VertexBuffer* vertexBuffer = renderDevice->createVertexBuffer(verticesSize, verticesArray);

				if (!vertexBuffer)
				{
					cout << "Failed to create Vertex Buffer." << endl;
					throw exception("Assimp mesh loading.");
				}

				vertexArrayObject->addVertexBuffer(vertexBuffer, 0, 3 * sizeof(float), 0, 3);

				/*
					For each number of primitives (mFace) of the mesh,
					iterate over each and push the indices into the indices vector.
				*/
				vector<int> indices;
				for (unsigned int a = 0; a < mesh->mNumFaces; a = a + 1)
				{
					aiFace temp = mesh->mFaces[a];
					for (unsigned int b = 0; b < temp.mNumIndices; b = b + 1)
					{
						unsigned int temp2 = temp.mIndices[b];
						indices.push_back(temp2);
					}
				}

				// Convert vector to array
				int* indicesArray = indices.data();

				IndexBuffer* indexBuffer = renderDevice->createIndexBuffer(indices.size() * sizeof(unsigned int), indicesArray);

				if (!indexBuffer)
				{
					cout << "Failed to create Index Buffer." << endl;
					throw exception("Assimp mesh loading.");
				}

				// Unbind VAO to prevent overriding errors
				vertexArrayObject->unbind();

				// Combine all into a mesh.
				Mesh* m = new Mesh(vertexArrayObject, indexBuffer);
				m->indicesLength = indices.size();

				if (!m)
				{
					cout << "Failed to create Mesh." << endl;
					throw exception("Assimp mesh loading.");
				}

				return m;
			}

			StaticMeshLoader::~StaticMeshLoader()
			{
			}
		}
	}
}