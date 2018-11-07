#include "World/WorldLoader.h"

#include <iostream>
#include "nlohmann/json.hpp"

#include "World/ObjectProperties.h"


using namespace nlohmann;
using namespace World;

WorldLoader::WorldLoader() = default;

WorldLoader::~WorldLoader() = default;

void WorldLoader::load(const char * filename)
{
	loadJson(readFile(filename));
}

std::ifstream WorldLoader::readFile(const char * filename)
{
	return std::ifstream(filename);
}

void WorldLoader::loadJson(std::ifstream input)
{
	json j;
	input >> j;

	int globalSize = j["tileheight"];

	auto layers = j["layers"];
	for (const auto &layer : layers)
	{
		if (layer["type"] == "objectgroup") {
			for (const auto &object : layer["objects"])
			{
				ObjectProperties p = object;
				json jb = p;
				std::cout << jb << std::endl;
			}
		}
	}

	std::cout << std::endl;
}
