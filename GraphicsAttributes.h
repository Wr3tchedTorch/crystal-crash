#pragma once
#include <string>
#include <SFML/Graphics/Rect.hpp>
#include "AnimatedGraphicsAttributes.h"

struct GraphicsAttributes
{
	std::string GraphicsId;
	sf::IntRect TextureRect;	

	AnimatedGraphicsAttributes Animation;
};