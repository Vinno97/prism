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
#include <memory>

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
			/// <returns>unique_ptr<Mesh></returns>
			unique_ptr<Mesh> StaticMeshLoader::loadMesh(std::string path, RenderDevice* renderDevice)
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
					cout << "No meshes found." << endl;
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
					cout << "Renderdevice could to create VAO. No Vertex Array Object found." << endl;
					throw exception("Assimp mesh loading.");
				}

				// Get the size of the vertices to provide the VertexBuffer with the right data.
				auto verticesSize = vertices.size() * sizeof(float);

				VertexBuffer* vertexBuffer = renderDevice->createVertexBuffer(verticesSize, verticesArray);

				if (!vertexBuffer)
				{
					cout << "Renderdevice could not create Vertex Buffer. No Vertex Buffer found." << endl;
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
					cout << "Renderdevice could not create IndexBuffer. No Index Buffer found." << endl;
					throw exception("Assimp mesh loading.");
				}

				// Vertex Array Object gets unbind for it is no longer needed.
				vertexArrayObject->unbind();

				// Combine all into a mesh.
				unique_ptr<Mesh> combinedMesh = make_unique<Mesh>(vertexArrayObject, indexBuffer);
				combinedMesh->indicesLength = indices.size();

				if (!combinedMesh)
				{
					cout << "Mesh creation failed. No mesh found." << endl;
					throw exception("Assimp mesh loading.");
				}

				return combinedMesh;
			}

			StaticMeshLoader::~StaticMeshLoader()
			{
			}
		}
	}
}