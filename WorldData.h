#pragma once
#include <nlohmann/json.hpp>
#include <memory>
#include "TilemapAttributes.h"
#include "GameObjectData.h"
#include <vector>

using json = nlohmann::json;

struct WorldData
{
	int   Id;
	float Gravity;
	int	  TilemapId;
	
	std::vector<GameObjectData> EntitiesData;

	void setTilemapAttributes(std::shared_ptr<TilemapAttributes> tilemap)
	{
		Tilemap   = tilemap;
		TilemapId = tilemap->Id;
	}

	const std::shared_ptr<TilemapAttributes> getTilemapAttributes() const
	{
		return Tilemap;
	}

private:
	std::shared_ptr<TilemapAttributes> Tilemap;
};

inline void to_json(json& j, const WorldData& pa)
{
	j =
	{
		{"id", pa.Id},
		{"gravity", pa.Gravity},
		{"tilemap_id", pa.TilemapId},
		{"entities", pa.EntitiesData}
	};
}

inline void from_json(const json& j, WorldData& pa)
{
	j.at("id").get_to(pa.Id);
	j.at("gravity").get_to(pa.Gravity);
	j.at("tilemap_id").get_to(pa.TilemapId);
	j.at("entities").get_to(pa.EntitiesData);
}