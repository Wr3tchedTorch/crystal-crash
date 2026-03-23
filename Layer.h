#pragma once
#include <nlohmann/json.hpp>
#include "Tile.h"
#include <vector>
#include <string>
#include <format>

using json = nlohmann::json;

struct Layer
{
	inline static const std::string LayerNameKey = "Layer_";

	int Id;	
	std::vector<Tile> Tiles;
	bool Collider;

	bool operator< (const Layer& other) const
	{
		return Id < other.Id;
	}

	bool operator> (const Layer& other) const
	{
		return Id > other.Id;
	}
};

inline void to_json(json& j, const Layer& pa)
{
	j =
	{
		{"name", std::format("{}{}", Layer::LayerNameKey, pa.Id)},
		{"tiles", pa.Tiles},
		{"collider", pa.Collider},
	};
}

inline void from_json(const json& j, Layer& pa)
{
	std::string name;
	j.at("name").get_to(name);
	pa.Id = std::stoi(name.substr(Layer::LayerNameKey.size()));

	j.at("collider").get_to(pa.Collider);
	j.at("tiles").get_to(pa.Tiles);
}