#pragma once
#include <types.h>
#include <id.h>
#include "nlohmann/json.hpp"
#include <string>
#include "ShapeAttributesConstants.h"

using json = nlohmann::json;

struct ShapeAttributes
{
	int Id = 0;
	b2ShapeType Type;
	std::string Name = "";

	virtual b2ShapeId createShape(b2BodyId body, const b2ShapeDef& shapeDef) = 0;

	static std::string typeToString(b2ShapeType type)
	{
		switch (type)
		{
		case b2_circleShape:
			return ShapeAttributesConstants::CircleShapeName;
		case b2_capsuleShape:
			return ShapeAttributesConstants::CapsuleShapeName;
		case b2_polygonShape:
			return ShapeAttributesConstants::PolygonShapeName;
		default:
			return "error: not found!";
		}
	}

	static b2ShapeType stringToType(std::string type)
	{
		if (type == ShapeAttributesConstants::CircleShapeName)
		{
			return b2_circleShape;
		}
		if (type == ShapeAttributesConstants::CapsuleShapeName)
		{
			return b2_capsuleShape;
		}
		if (type == ShapeAttributesConstants::PolygonShapeName)
		{
			return b2_polygonShape;
		}
	}

	virtual void parentToJson(json& j, const ShapeAttributes& sa) const
	{
		j["type"] = ShapeAttributes::typeToString(sa.Type);
		j["name"] = sa.Name;
	}

	virtual void parentFromJson(const json& j, ShapeAttributes& sa)
	{
		json type;
		j.at("type").get_to(type);

		sa.Type = ShapeAttributes::stringToType(type);

		j.at("name").get_to(sa.Name);
	}
};
