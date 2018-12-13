#include "World/WorldObject.h"

namespace World
{
	void to_json(nlohmann::json& j, const WorldObject& p)
	{
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
		if (p.additionalProperties.size() > 0)
		{
			j["properties"] = p.additionalProperties;
		}
	}

	void from_json(const nlohmann::json& j, WorldObject& p)
	{
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
			for (const ObjectProperties& ap : j.at("properties"))
			{
				p.additionalProperties[ap.name] = ap;
			}
		}
	}
}
