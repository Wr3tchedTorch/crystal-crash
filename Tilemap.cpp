#include "Tilemap.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <vector>
#include "Tile.h"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>

void Tilemap::updateVertices()
{
	m_Vertices.clear();

	sf::Vector2i spritesheetSize = sf::Vector2i(m_TilemapTexture.getSize()) / m_TileSize;

	for (auto& tile : m_Tiles)
	{
		float top  = m_TileSize * tile.GridPosition.y;
		float left = m_TileSize * tile.GridPosition.x;
		float bottom = top  + m_TileSize;
		float right  = left + m_TileSize;

		int uvX = tile.Id % spritesheetSize.x;
		int uvY = tile.Id / spritesheetSize.x;

		float uvTop    = m_TileSize * uvY;
		float uvLeft   = m_TileSize * uvX;
		float uvBottom = uvTop  + m_TileSize;
		float uvRight  = uvLeft + m_TileSize;

		m_Vertices.append({ { left,  top	}, sf::Color::White, { uvLeft,  uvTop	 }});
		m_Vertices.append({ { right, top	}, sf::Color::White, { uvRight, uvTop	 } });
		m_Vertices.append({ { left,  bottom }, sf::Color::White, { uvLeft,  uvBottom } });

		m_Vertices.append({ { right, top	}, sf::Color::White, { uvRight, uvTop	 } });
		m_Vertices.append({ { left,  bottom }, sf::Color::White, { uvLeft,  uvBottom } });
		m_Vertices.append({ { right, bottom }, sf::Color::White, { uvRight, uvBottom } });
	}
}

Tilemap::Tilemap(sf::Texture& tilemapTexture, std::vector<Tile> tiles, sf::Vector2i tilemapSize, int tileSize) : m_TilemapTexture(tilemapTexture), m_Tiles(tiles)
{
	m_TileSize	  = tileSize;
	m_TilemapSize = tilemapSize;

	m_Vertices.setPrimitiveType(sf::PrimitiveType::Triangles);

	updateVertices();
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &m_TilemapTexture;

	target.draw(m_Vertices, states);
}
