#pragma once

#include "World/LevelSerializer.h"
#include "EntityAssembler.h"

namespace World {
	class JSONSerializer : public LevelSerializer {
	public:
		virtual std::vector<WorldObject> deserialize(std::basic_istream<char> &input);
		virtual void serialize(std::vector<WorldObject> worldObjects, std::basic_ostream<char> &output);
	};
}

