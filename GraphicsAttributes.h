#pragma once
#include <string>
#include <SFML/Graphics/Rect.hpp>
#include "AnimatedGraphicsAttributes.h"
#include "nlohmann/json.hpp"
#include <memory>
#include "ShapeAttributes.h"

using json = nlohmann::json;

struct GraphicsAttributes
{
	int Id = 0;
	std::string ImageId = "";
	sf::IntRect TextureRect = sf::IntRect({ 0, 0 }, { 0, 0 });

	int ShapeId = 0;

	AnimatedGraphicsAttributes Animation;
	void setShape(std::shared_ptr<ShapeAttributes> shape)
	{
		Shape = shape;
		ShapeId = shape->Id;
	}

	const std::shared_ptr<ShapeAttributes> getShape() const
	{
		return Shape;
	}

private:
	std::shared_ptr<ShapeAttributes> Shape;
};

inline void to_json(json& j, const GraphicsAttributes& ga)
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
		{ "image_filename", ga.ImageId},
		{ "frame_rect",  textureRectData},
		{ "animation", animationData },
		{ "shape_id", ga.ShapeId }
	};
}

inline void from_json(const json& j, GraphicsAttributes& ga)
{
	j.at("image_filename").get_to(ga.ImageId);
	
	json textureRectData;
	j.at("frame_rect").get_to(textureRectData);
	j.at("shape_id").get_to(ga.ShapeId);

	ga.TextureRect.position.x = textureRectData.at("position").at("x").get<float>();
	ga.TextureRect.position.y = textureRectData.at("position").at("y").get<float>();

	ga.TextureRect.size.x = textureRectData.at("size").at("width").get<float>();
	ga.TextureRect.size.y = textureRectData.at("size").at("height").get<float>();

	ga.Animation = j.at("animation");
}