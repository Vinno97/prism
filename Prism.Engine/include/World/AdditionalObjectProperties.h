#pragma once

#include <string>
#include "nlohmann/json.hpp"

namespace World {
	struct AdditionalObjectProperties {
		std::string name;
		std::string type;
		std::string value;
	};

	void to_json(nlohmann::json& j, const AdditionalObjectProperties& p) {
		j = nlohmann::json{ 
			{"name", p.name}, 
			{"type", p.type}, 
			{"value", p.value}, 
		};
	}

	void from_json(const nlohmann::json& j, AdditionalObjectProperties& p) {
		j.at("name").get_to(p.name);
		j.at("type").get_to(p.type);
		j.at("value").get_to(p.value);
	}
}