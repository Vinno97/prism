#pragma once

#include <string>
#include "nlohmann/json.hpp"


namespace World {
	struct ObjectProperties {
		std::string name;
		std::string type;
		std::string value;
	};

	void to_json(nlohmann::json& j, const ObjectProperties& p);

	void from_json(const nlohmann::json& j, ObjectProperties& p);
}
