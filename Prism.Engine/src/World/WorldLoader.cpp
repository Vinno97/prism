#include "World/WorldLoader.h"

#include <iostream>
#include "nlohmann/json.hpp"

#include "World/WorldObject.h"
#include "World/JSONSerializer.h"
#include "Util/FileReader.h"

using namespace nlohmann;
using namespace World;

void LevelManager::load(const std::string& worldName, ECS::EntityManager &entityManager)
{
	auto stream = Util::FileReader().readResourceIntoStream("levels/" + worldName + ".json");
	serializer->deserialize(stream);
}

void World::LevelManager::save(const std::string& worldName, ECS::EntityManager &entityManager)
{	
	auto output = std::ofstream(worldName);
	std::vector<WorldObject> test;
	serializer->serialize(test, output);
}

World::LevelManager::LevelManager()
{
	serializer = std::make_unique<JSONSerializer>();
}

//void LevelManager::loadJson(std::ifstream input, EntityAssembler& entityAssembler)
//{
//	json j;
//	input >> j;
//
//	int tileHeight = j["tileheight"];
//	int tileWidth = j["tilewidth"];
//
//
//
//	auto layers = j["layers"];
//	for (const auto &layer : layers)
//	{
//		if (layer["type"] == "objectgroup") {
//			for (const auto &object : layer["objects"])
//			{
//				WorldObject p = object;
//				p.x /= tileWidth;
//				p.y /= tileHeight;
//				p.width /= tileWidth;
//				p.height /= tileHeight;
//
//				entityAssembler.assemble(p);
//
//				//json jb = p;
//				//std::cout << jb << std::endl;
//			}
//		}
//	}
//
//	std::cout << std::endl;
//}
