#pragma once
#include <string>
#include "GraphicsAttributes.h"
#include "ShapeAttributes.h"
#include <memory>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct ProjectileAttributes
{	
	int Id;
	std::string Name = "";
	float MaxSpeed = 0;
	float Damage = 0;

	std::shared_ptr<ShapeAttributes> Shape;
	GraphicsAttributes Graphics;
};

inline void to_json(json& j, const ProjectileAttributes& pa)
{
	j =
	{ 
		{"id", pa.Id}, 
		{"name", pa.Name},
		{"max_speed", pa.MaxSpeed}, 
		{"damage", pa.Damage},
		{"graphics_id", pa.Graphics.Id},
	};

	if (pa.Shape)
	{
		j["shape_id"] = { pa.Shape->Id };
	}
	else
	{
		j["shape_id"] = { "error: not found!" };
	}
}

inline void from_json(const json& j, ProjectileAttributes& pa)
{
	j.at("id").get_to(pa.Id);
	j.at("name").get_to(pa.Name);
	j.at("max_speed").get_to(pa.MaxSpeed);
	j.at("damage").get_to(pa.Damage);
}