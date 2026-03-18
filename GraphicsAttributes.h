#pragma once
#include <string>
#include <SFML/Graphics/Rect.hpp>
#include <memory>
#include "AnimatedGraphicsAttributes.h"

struct GraphicsAttributes
{
	std::string GraphicsId;
	sf::IntRect TextureRect;	

	std::shared_ptr<AnimatedGraphicsAttributes> Animation;
};