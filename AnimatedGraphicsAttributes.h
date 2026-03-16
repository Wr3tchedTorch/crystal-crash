#pragma once
#include "GraphicsAttributes.h"
#include <SFML/System/Vector2.hpp>

struct AnimatedGraphicsAttributes : GraphicsAttributes
{
	int FrameCount = 0;
	int AnimationCount = 0;

	bool Loop = false;

	float DelayBetweenFrames = 0.0f;
	float DelayBeforeAnimationStart = 0.0f;

	sf::Vector2i SpriteSize;
};