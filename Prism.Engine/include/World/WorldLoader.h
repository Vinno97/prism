#pragma once

#include <fstream>
#include "EntityAssembler.h"
#include "ECS/EntityManager.h"
#include "World/LevelSerializer.h"
#include <memory>

namespace World {
	// TODO: Verzin een naam die zowel "LevelLoader", als "LevelSaver" betekent of insinueert.
	class LevelManager
	{

	public:
		LevelManager();
		//LevelManager(EntityAssembler &entityAssembler_) : entityAssembler(entityAssembler_) : {}

		~LevelManager() = default;

		void load(const char* filename, ECS::EntityManager& entityManager);
		void save(const char* filename, ECS::EntityManager& entityManager);

		void setSerializer(std::unique_ptr<LevelSerializer> serializer_) {
			serializer = std::move(serializer_);
		}
	private:
		std::ifstream readFile(const char* filename);
		std::unique_ptr<LevelSerializer> serializer;
		//void loadJson(std::ifstream input, EntityAssembler& entityAssembler);
	};
}
