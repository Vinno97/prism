#include "World/TerrainGenerator.h"
#include "Renderer/Graphics/Models/Model.h"
#include <Math/Vector3f.h>
#include <memory>
#include <ctime>
#include <random>
#include <iostream>
#include <cstdlib>
#include <Renderer/Graphics/VertexBuffer.h>
#include <Renderer/Graphics/VertexArrayObject.h>
#include <Renderer/Graphics/RenderDevice.h>
#include <Renderer/Graphics/OpenGL/OGLRenderDevice.h>

using namespace Math;
using namespace Renderer::Graphics;
using namespace Renderer::Graphics::Models;
using namespace Renderer::Graphics::OpenGL;

namespace World {
	TerrainGenerator::TerrainGenerator()
	{
	}

	std::unique_ptr<Model> TerrainGenerator::generateTerrain(int width, int height) {
		std::default_random_engine generator;
		std::uniform_real_distribution<float> distribution(0.0, 1.7);

		heightMap.resize(height, std::vector<float>(width, -1));
		//Fill height map
		float i = 0;
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				heightMap[y][x] = distribution(generator)/10;
			}
		}

		for(int y = 0; y < height-1; y++) {
			for(int x = 0; x < width-1; x++) {
				if(heightMap.size()-1 == y) {
					continue;
				}
				if(heightMap[y].size()-1 == y) {
					continue;
				}
				
				Vector3f topLeft(x, heightMap[y][x], y);
				Vector3f topRight(x+1, heightMap[y][x+1], y);
				Vector3f bottomLeft(x, heightMap[y+1][x], y+1);
				Vector3f bottomRight(x+1, heightMap[y+1][x+1], y+1);
				

				packTriangle(topLeft, bottomLeft, topRight);
				packTriangle(topRight, bottomLeft, bottomRight);
			}
		}

		RenderDevice* renderDevice = OGLRenderDevice::getRenderDevice();
		std::unique_ptr<VertexArrayObject> vertexArrayObject = renderDevice->createVertexArrayobject();

		auto verticesSize = positions.size() * sizeof(float);
		float* verticesArray = positions.data();
		std::unique_ptr<VertexBuffer> vertexBuffer = renderDevice->createVertexBuffer(verticesSize, verticesArray);
		vertexArrayObject->addVertexBuffer(move(vertexBuffer), 0, 3 * sizeof(float), 0, 3);

		auto normalsSize = normals.size() * sizeof(float);
		float* normalsArray = normals.data();
		std::unique_ptr<VertexBuffer> normalBuffer = renderDevice->createVertexBuffer(normalsSize, normalsArray);
		vertexArrayObject->addVertexBuffer(move(normalBuffer), 1, 3 * sizeof(float), 0, 3);

		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(move(vertexArrayObject));
		mesh->isIndiced = false;
		mesh->verticesLength = positions.size() / 3;

		std::unique_ptr<Model> model = std::make_unique<Model>(mesh);

		return model;
	}
	void TerrainGenerator::packTriangle(Vector3f v1, Vector3f v2, Vector3f v3)
	{
		positions.push_back(v1.x);
		positions.push_back(v1.y);
		positions.push_back(v1.z);
		
		positions.push_back(v2.x);
		positions.push_back(v2.y);
		positions.push_back(v2.z);
		
		positions.push_back(v3.x);
		positions.push_back(v3.y);
		positions.push_back(v3.z);

		glm::vec3 n1{ v1.x, v1.y, v1.z };
		glm::vec3 n2{ v2.x, v2.y, v2.z };
		glm::vec3 n3{ v3.x, v3.y, v3.z };
		
		//Calc normal
		glm::vec3 dir = glm::cross((n2 -n1), ((n3 - n1)));
		glm::vec3 gNorm = glm::normalize(dir);
		Vector3f norm{ gNorm.x, gNorm.y, gNorm.z };
				
		normals.push_back(norm.x);
		normals.push_back(norm.y);
		normals.push_back(norm.z);
		
		normals.push_back(norm.x);
		normals.push_back(norm.y);
		normals.push_back(norm.z);
		
		normals.push_back(norm.x);
		normals.push_back(norm.y);
		normals.push_back(norm.z);
	}
}
