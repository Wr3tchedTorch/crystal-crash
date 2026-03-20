#pragma once
#include <types.h>
#include <id.h>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

struct ShapeAttributes
{
	b2ShapeType Type;

	virtual b2ShapeId createShape(b2BodyId body, const b2ShapeDef& shapeDef) = 0;
};

void to_json(json& j, const ShapeAttributes& sa)
{
	j = json { 
		{ "type", sa.Type }
	};
}

void from_json(const json& j, ShapeAttributes& sa)
{
	j.at("type").get_to(sa.Type);
}