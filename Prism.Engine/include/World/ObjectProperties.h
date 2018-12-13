#pragma once

#include <string>
#include "nlohmann/json.hpp"


namespace World
{
	struct ObjectProperties
	{
		ObjectProperties() = default;

		ObjectProperties(std::string name_, std::string value_) : name(name_), value(value_)
		{
		};
		std::string name;
		std::string value;
	};

	void to_json(nlohmann::json& j, const ObjectProperties& p);

	void from_json(const nlohmann::json& j, ObjectProperties& p);
}
