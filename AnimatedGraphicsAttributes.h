#pragma once

struct AnimatedGraphicsAttributes
{
	int FrameCount = 0;
	int AnimationCount = 0;

	bool Loop = false;

	float DelayBetweenFrames = 0.0f;
	float DelayBeforeAnimationStart = 0.0f;
};