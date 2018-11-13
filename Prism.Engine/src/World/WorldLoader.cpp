#include "World/WorldLoader.h"

#include <iostream>
#include "nlohmann/json.hpp"

#include "World/WorldObject.h"
#include "World/JSONSerializer.h"
#include "Util/FileSystem.h"
#include <sstream>

using namespace nlohmann;
using namespace World;

void LevelManager::load(const std::string& worldName, ECS::EntityManager &entityManager)
{
	auto stream{ Util::FileReader().readResourceIntoStream(worldName + ".json") };
	auto worldObjects{ serializer->deserialize(stream) };
	for (const auto& object : worldObjects) {
		int entity = entityManager.createEntity();
		entityAssembler->assemble(entity, object, entityManager);
	}
}

void World::LevelManager::save(const std::string& worldName, ECS::EntityManager &entityManager)
{	
	std::vector<WorldObject> objects;

	auto entities = entityManager.getAllEntities();
	for (const auto& entity : entities) {
		WorldObject object;
		entityAssembler->disassemble(entity, object, entityManager);
		objects.push_back(object);
	}
	//std::ofstream output{ worldName };

	std::stringstream output;
	serializer->serialize(objects, output);
	std::string buffer;
	output >> buffer;
	Util::FileReader().saveStringIntoResource(worldName + ".json", buffer);
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
