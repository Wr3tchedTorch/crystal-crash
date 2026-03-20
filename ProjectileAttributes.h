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
	std::string Name;
	float MaxSpeed;
	float Damage;

	std::shared_ptr<ShapeAttributes> Shape;
	GraphicsAttributes	  Graphics;
};

void to_json(json& j, const ProjectileAttributes& pa)
{
	j += json
	{ 
		{"id", pa.Id}, 
		{"name", pa.Name},
		{"max_speed", pa.MaxSpeed}, 
		{"damage", pa.Damage},
		{"graphics", pa.Graphics}
	};
	
	pa.Shape->to_json(j, *pa.Shape.get());
}

void from_json(json& j, ProjectileAttributes& pa)
{
	j.at("id").get_to(pa.Id);
	j.at("name").get_to(pa.Name);
	j.at("max_speed").get_to(pa.MaxSpeed);
	j.at("damage").get_to(pa.Damage);
	j.at("graphics").get_to(pa.Graphics);

	pa.Shape->from_json(j, *pa.Shape.get());
}