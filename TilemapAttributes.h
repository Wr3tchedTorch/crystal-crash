#pragma once
#include <vector>
#include <nlohmann/json.hpp>
#include "Layer.h"

using json = nlohmann::json;

struct TilemapAttributes
{
	int Id;
	int TileSize  = 32;
	int MapWidth  = 31;
	int MapHeight = 7;
	
	std::vector<Layer> Layers;
};

inline void to_json(json& j, const TilemapAttributes& pa)
{
	j =
	{
		{"tile_size", pa.TileSize},
		{"map_width", pa.MapWidth},
		{"map_height", pa.MapHeight},
		{"layers", pa.Layers}
	};
}

inline void from_json(const json& j, TilemapAttributes& pa)
{
	j.at("tile_size").get_to(pa.TileSize);
	j.at("map_width").get_to(pa.MapWidth);
	j.at("map_height").get_to(pa.MapHeight);
	j.at("layers").get_to(pa.Layers);
}