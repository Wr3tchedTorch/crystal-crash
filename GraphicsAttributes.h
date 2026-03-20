#pragma once
#include <string>
#include <SFML/Graphics/Rect.hpp>
#include "AnimatedGraphicsAttributes.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

struct GraphicsAttributes
{
	std::string GraphicsId  = "";
	sf::IntRect TextureRect = sf::IntRect({0, 0}, {0, 0});

	AnimatedGraphicsAttributes Animation;
};

void to_json(json& j, const GraphicsAttributes& ga)
{	
	json textureRectData =
	{
		{
			"position",
			{
				{"x", ga.TextureRect.position.x},
				{"y", ga.TextureRect.position.y}
			}
		},
		{
			"size",
			{
				{"width", ga.TextureRect.size.x},
				{"height", ga.TextureRect.size.y}
			}
		}
	};

	json animationData = ga.Animation;

	j = json{
		{ "image_filename", ga.GraphicsId},
		{ "frame_rect",  textureRectData},
		{ "animation", animationData }
	};
}

void from_json(const json& j, GraphicsAttributes& ga)
{
	j.at("image_filename").get_to(ga.GraphicsId);
	
	json textureRectData;
	j.at("frame_rect").get_to(textureRectData);

	ga.TextureRect.position.x = textureRectData.at("position").at("x").get<float>();
	ga.TextureRect.position.y = textureRectData.at("position").at("y").get<float>();

	ga.TextureRect.size.x = textureRectData.at("size").at("x").get<float>();
	ga.TextureRect.size.y = textureRectData.at("size").at("y").get<float>();

	j.at("animation").get_to(ga.Animation);
}