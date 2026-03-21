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
	float Damage   = 0;

	int ShapeId	   = 0;
	int GraphicsId = 0;

	void setShape(std::shared_ptr<ShapeAttributes> shape)
	{
		Shape   = shape;
		ShapeId = shape->Id;
	}

	const std::shared_ptr<ShapeAttributes> getShape() const
	{
		return Shape;
	}

	void setGraphics(std::shared_ptr<GraphicsAttributes> graphics)
	{
		Graphics   = graphics;
		GraphicsId = graphics->Id;
	}
	
	const std::shared_ptr<GraphicsAttributes> getGraphics() const
	{
		return Graphics;
	}

private:
	std::shared_ptr<ShapeAttributes> Shape;
	std::shared_ptr<GraphicsAttributes> Graphics;
};

inline void to_json(json& j, const ProjectileAttributes& pa)
{
	j =
	{ 
		{"id", pa.Id}, 
		{"name", pa.Name},
		{"max_speed", pa.MaxSpeed}, 
		{"damage", pa.Damage},
		{"shape_id", pa.ShapeId},
		{"graphics_id", pa.GraphicsId}
	};
}

inline void from_json(const json& j, ProjectileAttributes& pa)
{
	j.at("id").get_to(pa.Id);
	j.at("name").get_to(pa.Name);
	j.at("max_speed").get_to(pa.MaxSpeed);
	j.at("damage").get_to(pa.Damage);
	j.at("shape_id").get_to(pa.ShapeId);
	j.at("graphics_id").get_to(pa.GraphicsId);
}