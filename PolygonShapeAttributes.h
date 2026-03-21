#pragma once
#include <math_functions.h>
#include "ShapeAttributes.h"
#include <id.h>
#include <vector>
#include <collision.h>
#include <iostream>
#include <format>
#include <box2d.h>
#include <types.h>
#include <string>

struct PolygonShapeAttributes : public ShapeAttributes
{
	std::vector<b2Vec2> Points;
	float Radius = 0.0f;

	PolygonShapeAttributes()
	{
		Type = b2_polygonShape;
	}
	
	b2ShapeId createShape(b2BodyId body, const b2ShapeDef& shapeDef) override
	{
		b2Hull hull = b2ComputeHull(Points.data(), Points.size());
		if (hull.count == 0)
		{
#ifdef _DEBUG
			std::cout << std::format("[PolygonShapeAttributes - 20] Invalid hull for polygon, number of points: {}", Points.size());
#endif // _DEBUG
			return b2ShapeId();
		}

		b2Polygon polygon = b2MakePolygon(&hull, Radius);

		return b2CreatePolygonShape(body, &shapeDef, &polygon);
	}
};

inline void to_json(json& j, const PolygonShapeAttributes& psa)
{
	psa.parentToJson(j, psa);

	json pointsData = json::array();
	for (const auto& p : psa.Points)
	{
		pointsData.push_back({ {"x", p.x}, {"y", p.y} });
	}

	j["points"] = pointsData;
}

inline void from_json(const json& j, PolygonShapeAttributes& psa)
{
	psa.parentFromJson(j, psa);

	json pointsData = json::array();
	j.at("points").get_to(pointsData);

	psa.Points.clear();
	psa.Points.resize(pointsData.size());

	for (const auto& p : pointsData)
	{
		psa.Points.push_back({ p.at("x").get<float>(), p.at("y").get<float>() });
	}
}