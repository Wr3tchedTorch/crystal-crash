#pragma once
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <SFML/System/Vector2.hpp>

using json = nlohmann::json;

struct GameObjectData
{
	int Id;
	int EntityId;
	std::string Type;
	sf::Vector2f Position;
};

inline void to_json(json& j, const GameObjectData& pa)
{
	j =
	{
		{"id", pa.Id},
		{"entity_id", pa.EntityId},
		{"type", pa.Type},
		{
			"position",
			{
				{"x", pa.Position.x},
				{"y", pa.Position.y}
			}
		},
	};
}

inline void from_json(const json& j, GameObjectData& pa)
{
	j.at("id").get_to(pa.Id);
	j.at("entity_id").get_to(pa.EntityId);
	j.at("type").get_to(pa.Type);
	
	pa.Position.x = j.at("position").at("x").get<float>();
	pa.Position.y = j.at("position").at("y").get<float>();
}