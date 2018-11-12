#include "World/ObjectProperties.h"

namespace World {
	void to_json(nlohmann::json& j, const ObjectProperties& p) {
		j = nlohmann::json{
			{"name", p.name},
			{"type", p.type},
			{"value", p.value},
		};
	}

	void from_json(const nlohmann::json& j, ObjectProperties& p) {
		j.at("name").get_to(p.name);
		j.at("type").get_to(p.type);
		j.at("value").get_to(p.value);
	}
}
