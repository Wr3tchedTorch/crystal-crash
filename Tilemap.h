#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <vector>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include "Layer.h"
#include <SFML/Graphics/Texture.hpp>
#include "TilemapAttributes.h"
#include <memory>

class Tilemap : public sf::Drawable
{
private:
	inline static const int VerticesPerTile = 6;

	sf::VertexArray m_Vertices;
	sf::Texture& m_TilemapTexture;

	std::shared_ptr<TilemapAttributes> m_Attributes;

	void updateVertices();

public:
	Tilemap(sf::Texture& tilemapTexture, std::shared_ptr<TilemapAttributes> attributes);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

