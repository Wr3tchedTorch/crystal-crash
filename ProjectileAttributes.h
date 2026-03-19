#pragma once
#include <string>
#include "GraphicsAttributes.h"
#include "ShapeAttributes.h"
#include <memory>

struct ProjectileAttributes
{	
	std::string Name;
	float MaxSpeed;
	float Damage;

	std::shared_ptr<ShapeAttributes> Shape;
	GraphicsAttributes	  Graphics;
};

