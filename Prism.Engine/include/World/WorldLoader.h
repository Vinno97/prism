#pragma once

#include <map>
#include <fstream>
#include "World/Assemblers/BaseAssembler.h"
#include "World/Assemblers/EntityAssembler.h"
#include "ECS/EntityManager.h"
#include "World/LevelSerializer.h"
#include "World/JSONSerializer.h"
#include <memory>

namespace World {
	// TODO: Verzin een naam die zowel "LevelLoader", als "LevelSaver" betekent of insinueert.
	class LevelManager
	{

	public:
		LevelManager() : LevelManager(std::make_unique<Assemblers::EntityAssembler>()) {};

		LevelManager(std::unique_ptr<Assemblers::BaseAssembler> &&entityAssembler_) 
			: LevelManager(std::move(entityAssembler_), std::make_unique<JSONSerializer>()) {}

		LevelManager(std::unique_ptr<Assemblers::BaseAssembler> &&entityAssembler_, std::unique_ptr<LevelSerializer> &&jsonSerializer_) :
			entityAssembler(std::move(entityAssembler_)), serializer(std::move(jsonSerializer_)) {}

		~LevelManager() = default;

		void load(const std::string& worldName, ECS::EntityManager& entityManager);
		void save(const std::string& worldName, ECS::EntityManager& entityManager);

		void setSerializer(std::unique_ptr<LevelSerializer> &&serializer_) {
			serializer = std::move(serializer_);
		}

		void setEntityAssembler(std::unique_ptr<Assemblers::EntityAssembler> &&entityAssembler_) {
			entityAssembler = std::move(entityAssembler_);
		}
	private:
		std::unique_ptr<LevelSerializer> serializer;
		std::unique_ptr<Assemblers::BaseAssembler> entityAssembler;

		//std::multimap<int, std::unique_ptr<Assemblers::BaseAssembler>> assemblers;
		//std::ifstream readFile(const char* filename);
		//void loadJson(std::ifstream input, EntityAssembler& entityAssembler);
	};
}
