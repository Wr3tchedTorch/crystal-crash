#pragma once
#include "GraphicsAttributes.h"

struct AnimatedGraphicsAttributes : GraphicsAttributes
{
	int FrameCount;
	bool Loop = false;
	float DelayBetweenFrames;
	float DelayBeforeAnimationStart;
};