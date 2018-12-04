#pragma once

#include <vector>
#include <memory>
#include <Math/Vector3.h>
#include "Renderer/Graphics/Models/Model.h"

namespace World {
	class TerrainGenerator
	{
	public:
		TerrainGenerator();
		std::unique_ptr<Renderer::Graphics::Models::Model> generateTerrain(int width, int height);
	private:
		std::vector<float> positions;
		std::vector<float> colours;
		std::vector<float> normals;
		std::vector<std::vector<float>> heightMap;
		void packTriangle(Math::Vector3f v1, Math::Vector3f v2, Math::Vector3f v3);
	};
}