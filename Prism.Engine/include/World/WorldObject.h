#pragma once

#include <string>
#include <map>
#include "nlohmann/json.hpp"
#include "ECS/EntityManager.h"

#include "ObjectProperties.h"

namespace World {
	struct WorldObject {
		int id;
		int gid;
		bool visible;
		float width;
		float height;
		float rotation;
		float x;
		float y;
		std::string name;
		std::string type;
		std::map<std::string, ObjectProperties> additionalProperties;
	};

	void to_json(nlohmann::json& j, const WorldObject& o);

	void from_json(const nlohmann::json& j, WorldObject& o);

	void to_entitymanager(ECS::EntityManager& entityManager, const WorldObject& p);

	void from_entitymanager(const ECS::EntityManager& entityManager, WorldObject& o);
}
