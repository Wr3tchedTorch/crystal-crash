#pragma once
#include <types.h>
#include <id.h>

struct ShapeAttributes
{
	b2ShapeType Type;

	virtual b2ShapeId createShape(b2BodyId body, b2ShapeDef& shapeDef) = 0;
};