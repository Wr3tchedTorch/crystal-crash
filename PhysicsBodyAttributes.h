#pragma once
#include <types.h>
#include <memory>

struct PhysicsBodyAttributes
{
	std::shared_ptr<b2BodyDef>  BodyDefinition;
	std::shared_ptr<b2ShapeDef> ShapeDefinition;
};