#pragma once

#include <utility>
#include <map>
#include <string>

#include <SFML/System/Vector2.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct TilemapCollisionData
{
	int Id = 0;	
	std::map<std::string, std::pair<sf::Vector2f, sf::Vector2f>> CollisionCoordinates = 
	{
		{ "top", {{0, 0}, {0, 0}} },
		{ "bottom", {{0, 0}, {0, 0}} },
		{ "left", {{0, 0}, {0, 0}} },
		{ "right", {{0, 0}, {0, 0}} },
	};

	inline static const std::string Sides[] = { "top", "bottom", "left", "right" };
};

inline void to_json(json& j, const TilemapCollisionData& pa)
{	
	json data = json();
	for (auto& side : TilemapCollisionData::Sides)
	{
		auto pointA = pa.CollisionCoordinates.at(side).first;
		auto pointB = pa.CollisionCoordinates.at(side).second;

		data[side] =
		{
			{
				pointA.x,
				pointA.y
			},
			{
				pointB.x,
				pointB.y
			},
		};
	}

	j["collision_data"] = data;
}

inline void from_json(const json& j, TilemapCollisionData& pa)
{	
	json data = j.at("collision_data");	

	for (auto& side : TilemapCollisionData::Sides)
	{
		pa.CollisionCoordinates[side].first.x = data.at(side)[0][0];
		pa.CollisionCoordinates[side].first.y = data.at(side)[0][1];

		pa.CollisionCoordinates[side].second.x = data.at(side)[1][0];
		pa.CollisionCoordinates[side].second.y = data.at(side)[1][1];
	}
}