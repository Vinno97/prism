#include "World/WorldLoader.h"

#include <iostream>
#include "nlohmann/json.hpp"

#include "World/WorldObject.h"
#include "Util/FileReader.h"

using namespace nlohmann;
using namespace World;

void WorldLoader::load(const std::string& worldName, EntityAssembler& entityAssembler)
{
	auto stream = Util::FileReader().readResourceIntoStream("levels/" + worldName + ".json");
	loadJson(stream, entityAssembler);
}

std::ifstream WorldLoader::readFile(const char * filename)
{
	return std::ifstream(filename);
}

void WorldLoader::loadJson(std::ifstream& input, EntityAssembler& entityAssembler)
{
	json j;
	input >> j;

	int tileHeight = j["tileheight"];
	int tileWidth = j["tilewidth"];

	auto layers = j["layers"];
	for (const auto &layer : layers)
	{
		if (layer["type"] == "objectgroup") {
			for (const auto &object : layer["objects"])
			{
				WorldObject p = object;
				p.x /= tileWidth;
				p.y /= tileHeight;
				p.width /= tileWidth;
				p.height /= tileHeight;

				entityAssembler.assemble(p);

				//json jb = p;
				//std::cout << jb << std::endl;
			}
		}
	}

	std::cout << std::endl;
}
