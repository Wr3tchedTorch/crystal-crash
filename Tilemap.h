#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <vector>
#include "Tile.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

class Tilemap : public sf::Drawable
{
private:
	inline static const int VerticesPerTile = 6;

	sf::VertexArray m_Vertices;
	sf::Texture& m_TilemapTexture;

	sf::Vector2i m_TilemapSize;
	std::vector<Tile> m_Tiles;

	int m_TileSize;

	void updateVertices();

public:
	Tilemap(sf::Texture& tilemapTexture, std::vector<Tile> tiles, sf::Vector2i tilemapSize, int tileSize);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

