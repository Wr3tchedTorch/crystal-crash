#pragma once
#include <SFML/System/Vector2.hpp>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

struct Tile
{
	int Id;
	sf::Vector2i GridPosition;
};

inline void to_json(json& j, const Tile& pa)
{
	j =
	{
		{"id", pa.Id},
		{"x", pa.GridPosition.x},
		{"y", pa.GridPosition.y},
	};
}

inline void from_json(const json& j, Tile& pa)
{
	std::string idString;
	j.at("id").get_to(idString);

	pa.Id = std::stoi(idString);

	j.at("x").get_to(pa.GridPosition.x);
	j.at("y").get_to(pa.GridPosition.y);
}