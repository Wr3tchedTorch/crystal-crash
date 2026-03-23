#include "Tilemap.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <vector>
#include "Tile.h"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include "TilemapAttributes.h"
#include <algorithm>
#include "Layer.h"

void Tilemap::updateVertices()
{
	m_Vertices.clear();

	sf::Vector2i spritesheetSize = sf::Vector2i(m_TilemapTexture.getSize()) / m_Attributes->TileSize;

	for (auto& layer : m_Attributes->Layers)
	{
		for (auto& tile : layer.Tiles)
		{
			float top  = m_Attributes->TileSize * tile.GridPosition.y;
			float left = m_Attributes->TileSize * tile.GridPosition.x;
			float bottom = top  + m_Attributes->TileSize;
			float right  = left + m_Attributes->TileSize;

			int uvX = tile.Id % spritesheetSize.x;
			int uvY = tile.Id / spritesheetSize.x;

			float uvTop  = m_Attributes->TileSize * uvY;
			float uvLeft = m_Attributes->TileSize * uvX;
			float uvBottom = uvTop  + m_Attributes->TileSize;
			float uvRight  = uvLeft + m_Attributes->TileSize;

			m_Vertices.append({ { left,  top	}, sf::Color::White, { uvLeft,  uvTop	 } });
			m_Vertices.append({ { right, top	}, sf::Color::White, { uvRight, uvTop	 } });
			m_Vertices.append({ { left,  bottom }, sf::Color::White, { uvLeft,  uvBottom } });

			m_Vertices.append({ { right, top	}, sf::Color::White, { uvRight, uvTop	 } });
			m_Vertices.append({ { left,  bottom }, sf::Color::White, { uvLeft,  uvBottom } });
			m_Vertices.append({ { right, bottom }, sf::Color::White, { uvRight, uvBottom } });
		}
	}
}

Tilemap::Tilemap(sf::Texture& tilemapTexture, std::shared_ptr<TilemapAttributes> attributes) : m_TilemapTexture(tilemapTexture), m_Attributes(attributes)
{
	m_Vertices.setPrimitiveType(sf::PrimitiveType::Triangles);

	std::sort(m_Attributes->Layers.begin(), m_Attributes->Layers.end(), std::greater<Layer>());

	updateVertices();
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &m_TilemapTexture;

	target.draw(m_Vertices, states);
}
