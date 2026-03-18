#pragma once
#include <string>
#include "GraphicsAttributes.h"
#include "PhysicsBodyAttributes.h"
#include "ShapeAttributes.h"
#include <memory>

struct ProjectileAttributes
{	
	std::string Name;
	float MaxSpeed;
	float Damage;

	std::unique_ptr<ShapeAttributes> Shape;

	GraphicsAttributes	  Graphics;
	PhysicsBodyAttributes Physics;
};

