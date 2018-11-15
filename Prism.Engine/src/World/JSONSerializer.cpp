#include "World/JSONSerializer.h"
#include "nlohmann/json.hpp"

using namespace World;
using namespace nlohmann;

std::vector<WorldObject> World::JSONSerializer::deserialize(std::basic_istream<char>& input)
{
	std::vector<WorldObject> objects;

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
				WorldObject wo = object;
				wo.x /= tileWidth;
				wo.y /= tileHeight;
				wo.width /= tileWidth;
				wo.height /= tileHeight;

				objects.push_back(wo);
			}
		}
	}

	return objects;
}

void World::JSONSerializer::serialize(std::vector<WorldObject> worldObjects, std::basic_ostream<char>& output)
{
	json j;

	j["tileheight"] = 1;
	j["tilewidth"] = 1;

	j["layers"] = json::array();
	j["layers"][0]["id"] = 1;
	j["layers"][0]["name"] = "Objects";
	j["layers"][0]["type"] = "objectgroup";
	j["layers"][0]["objects"] = worldObjects;

	output << j;
}
