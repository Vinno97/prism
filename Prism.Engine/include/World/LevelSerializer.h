#pragma once

#include "ECS/EntityManager.h"
#include <vector>
#include "World/WorldObject.h"

namespace World {
	class LevelSerializer {
	public:
		virtual std::vector<WorldObject> deserialize(std::basic_istream<char> &input) = 0;
		virtual void serialize(std::vector<WorldObject> worldObjects, std::basic_ostream<char> &output) = 0;
	};
}
