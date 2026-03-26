#pragma once

#include <utility>

#include <SFML/System/Vector2.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct TilemapCollisionData
{
	int Id = 0;	
	std::pair<sf::Vector2f, sf::Vector2f> CollisionCoordinates = {};
};

inline void to_json(json& j, const Tile& pa)
{
	j =
	{
		{		
			1,
			{
				{"x", pa.CollisionCoordinates.first.x},
				{"y", pa.CollisionCoordinates.first.y}
			}
		},
		{
			2,
			{
				{"x", pa.CollisionCoordinates.second.x},
				{"y", pa.CollisionCoordinates.second.y}
			}
		}
	};
}

inline void from_json(const json& j, Tile& pa)
{
	j.at(1).at("x").get_to(pa.CollisionCoordinates.first.x);
	j.at(1).at("y").get_to(pa.CollisionCoordinates.first.y);

	j.at(2).at("x").get_to(pa.CollisionCoordinates.second.x);
	j.at(2).at("y").get_to(pa.CollisionCoordinates.second.y);
}