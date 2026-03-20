#pragma once
#include "nlohmann/json.hpp"

using json = nlohmann::json;

struct AnimatedGraphicsAttributes
{
	int FrameCount = 0;
	int AnimationCount = 0;

	bool Loop = false;

	float DelayBetweenFrames = 0.0f;
	float DelayBeforeAnimationStart = 0.0f;
};

void to_json(json& j, const AnimatedGraphicsAttributes& aga)
{
	j = json{
		{ "frame_count", aga.FrameCount},
		{ "animation_count",  aga.AnimationCount},
		{ "loop_enabled",  aga.Loop},
		{ "delay_between_frames",  aga.DelayBetweenFrames},
		{ "delay_before_animation_start",  aga.DelayBeforeAnimationStart}
	};
}

void from_json(const json& j, AnimatedGraphicsAttributes& aga)
{
	j.at("frame_count").get_to(aga.FrameCount);
	j.at("animation_count").get_to(  aga.AnimationCount );
	j.at("loop_enabled").get_to(  aga.Loop );
	j.at("delay_between_frames").get_to(  aga.DelayBetweenFrames );
	j.at("delay_before_animation_start").get_to(  aga.DelayBeforeAnimationStart);
}