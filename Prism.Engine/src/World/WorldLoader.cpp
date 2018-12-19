#include "World/WorldLoader.h"

#include <iostream>
#include "nlohmann/json.hpp"

#include "World/WorldObject.h"
#include "World/JSONSerializer.h"
#include "Util/FileSystem.h"
#include <sstream>

using namespace nlohmann;
using namespace World;

void LevelManager::load(const std::string &worldName, ECS::EntityManager &entityManager) {
    auto stream{Util::FileSystem().readResourceIntoStream(worldName)};
    auto worldObjects{serializer->deserialize(stream)};
    for (const auto &object : worldObjects) {
        int entity = entityManager.createEntity();
        entityAssembler->assemble(entity, object, entityManager);
    }
}

void World::LevelManager::save(const std::string &worldName, ECS::EntityManager &entityManager) {
    std::vector<WorldObject> objects;

    auto entities = entityManager.getAllEntities();
    for (const auto &entity : entities) {
        WorldObject object;
        entityAssembler->disassemble(entity, object, entityManager);
        objects.push_back(object);
    }

    std::stringstream output;
    serializer->serialize(objects, output);
    std::string buffer;
    output >> buffer;
    Util::FileSystem().saveStringIntoResource(worldName , buffer);
}
