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

struct PolygonShapeAttributes : public ShapeAttributes
{
	std::vector<b2Vec2> Points;
	float  Radius;
	
	b2ShapeId createShape(b2BodyId body, b2ShapeDef& shapeDef) override
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