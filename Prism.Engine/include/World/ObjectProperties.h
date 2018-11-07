#pragma once

#include <string>
#include <map>
#include <vector>

#include "nlohmann/json.hpp"

#include "AdditionalObjectProperties.h"

namespace World {
	struct ObjectProperties {
		int id;
		int gid;
		int visible;
		int width;
		int height;
		int rotation;
		int x;
		int y;
		std::string name;
		std::string type;
		std::map<std::string, AdditionalObjectProperties> additionalProperties;
		//std::vector<AdditionalObjectProperties> additionalProperties;
	};

	void to_json(nlohmann::json& j, const ObjectProperties& p) {
		j = nlohmann::json{ 
			{"id", p.id}, 
			{"gid", p.gid}, 
			{"visible", p.visible}, 
			{"width", p.width}, 
			{"height", p.height}, 
			{"rotation", p.rotation}, 
			{"x", p.x}, 
			{"y", p.y}, 
			{"name", p.name}, 
			{"type", p.type}
		};
		if (p.additionalProperties.size() > 0) {
			j["properties"] = p.additionalProperties;
		}
	}

	void from_json(const nlohmann::json& j, ObjectProperties& p) {
		j.at("gid").get_to(p.gid);
		j.at("id").get_to(p.id);
		j.at("visible").get_to(p.visible);
		j.at("width").get_to(p.width);
		j.at("height").get_to(p.height);
		j.at("rotation").get_to(p.rotation);
		j.at("x").get_to(p.x);
		j.at("y").get_to(p.y);
		if (j.find("properties") != j.end())
		{
			for (const AdditionalObjectProperties &ap : j.at("properties")) {
				p.additionalProperties[ap.name] = ap;
				//p.additionalProperties.push_back(ap);
			}
		}
	}
}
