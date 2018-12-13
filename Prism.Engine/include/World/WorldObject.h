#pragma once

#include <string>
#include <map>
#include "nlohmann/json.hpp"
#include "ECS/EntityManager.h"

#include "ObjectProperties.h"

namespace World
{
	struct WorldObject
	{
		int id = 0;
		int gid = 0;
		bool visible = false;
		float width = 1;
		float height = 1;
		float rotation = 0;
		float x = 0;
		float y = 0;
		std::string name = "";
		std::string type = "";
		std::map<std::string, ObjectProperties> additionalProperties;
	};

	void to_json(nlohmann::json& j, const WorldObject& o);

	void from_json(const nlohmann::json& j, WorldObject& o);

	void to_entitymanager(ECS::EntityManager& entityManager, const WorldObject& p);

	void from_entitymanager(const ECS::EntityManager& entityManager, WorldObject& o);
}
