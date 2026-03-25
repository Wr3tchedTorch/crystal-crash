#pragma once

#include <id.h>

#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "TilemapAttributes.h"

class Tilemap : public sf::Drawable, public sf::Transformable
{
private:
	inline static const int VerticesPerTile = 6;

	sf::VertexArray m_Vertices;
	sf::Texture& m_TilemapTexture;

	std::shared_ptr<TilemapAttributes> m_Attributes;

	b2WorldId m_WorldId;

	void updateVertices();

public:
	Tilemap(sf::Texture& tilemapTexture, std::shared_ptr<TilemapAttributes> attributes, b2WorldId worldId);

	void createCollision();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

