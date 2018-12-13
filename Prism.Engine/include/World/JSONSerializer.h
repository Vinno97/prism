#pragma once

#include "World/LevelSerializer.h"
#include "World/Assemblers/EntityAssembler.h"

namespace World
{
	class JSONSerializer : public LevelSerializer
	{
	public:
		std::vector<WorldObject> deserialize(std::basic_istream<char>& input) override;
		void serialize(std::vector<WorldObject> worldObjects, std::basic_ostream<char>& output) override;
	};
}
