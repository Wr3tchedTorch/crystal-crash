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
	json shapeData = *pa.Shape;

	j = json
	{ 
		{"id", pa.Id}, 
		{"name", pa.Name},
		{"max_speed", pa.MaxSpeed}, 
		{"damage", pa.Damage},
		{"shape", shapeData },

	};
}