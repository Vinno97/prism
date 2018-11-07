#pragma once

#include <fstream>
#include "EntityAssembler.h"

namespace World {
	class WorldLoader
	{

	public:
		WorldLoader() = default;
		WorldLoader(EntityAssembler &entityAssembler_) : entityAssembler(entityAssembler_) : {}

		~WorldLoader() = default;

		void load(const char* filename);

	private:
		std::ifstream readFile(const char* filename);
		void loadJson(std::ifstream input);
	};
}
