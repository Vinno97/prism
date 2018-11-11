#include "World/WorldLoader.h"

#include <iostream>
#include "nlohmann/json.hpp"

#include "World/WorldObject.h"
#include "World/JSONSerializer.h"


using namespace nlohmann;
using namespace World;


void World::LevelManager::load(const char * filename, ECS::EntityManager &entityManager)
{
	auto input = std::ifstream(filename);
	serializer->deserialize(input);
}

void World::LevelManager::save(const char * filename, ECS::EntityManager &entityManager)
{	
	auto output = std::ofstream(filename);
	std::vector<WorldObject> test;
	serializer->serialize(test, output);
}

World::LevelManager::LevelManager()
{
	serializer = std::make_unique<JSONSerializer>();
}

std::ifstream LevelManager::readFile(const char * filename)
{
	return std::ifstream(filename);
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
