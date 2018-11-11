#pragma once

#include <string>
#include <map>
#include "nlohmann/json.hpp"
#include "ECS/EntityManager.h"

#include "AdditionalObjectProperties.h"

namespace World {
	struct WorldObject {
		int id;
		int gid;
		int visible;
		int width;
		int height;
		int rotation;
		int x;
		int y;
		std::string name;
		std::string type;
		std::map<std::string, AdditionalObjectProperties> additionalProperties;
	};

	void to_json(nlohmann::json& j, const WorldObject& o);

	void from_json(const nlohmann::json& j, WorldObject& o);

	void to_entitymanager(ECS::EntityManager& entityManager, const WorldObject& p);

	void from_entitymanager(const ECS::EntityManager& entityManager, WorldObject& o);
}
