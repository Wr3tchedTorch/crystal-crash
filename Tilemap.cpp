#include "Tilemap.h"

#include <math_functions.h>
#include <id.h>
#include <box2d.h>
#include <types.h>

#include <vector>
#include <memory>
#include <algorithm>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "TilemapAttributes.h"
#include "Tile.h"
#include "Layer.h"
#include "GameEngine.h"
#include "Converter.h"

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

	createCollision();
}

Tilemap::Tilemap(sf::Texture& tilemapTexture, std::shared_ptr<TilemapAttributes> attributes, b2WorldId worldId) : m_TilemapTexture(tilemapTexture), m_Attributes(attributes), m_WorldId(worldId)
{
	m_Vertices.setPrimitiveType(sf::PrimitiveType::Triangles);

	std::sort(m_Attributes->Layers.begin(), m_Attributes->Layers.end(), std::greater<Layer>());

	updateVertices();
}

void Tilemap::createCollision()
{
	std::vector<b2Vec2> chain{};

	for (int i = 0; i < GameEngine::Resolution.x; i += GameEngine::Resolution.x / 8)
	{
		b2Vec2 position = { converter::pixelsToMeters(i), converter::pixelsToMeters(GameEngine::Resolution.y / 2.0f + 200.0f) };
		chain.push_back(position);
	}

	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_staticBody;

	b2BodyId body = b2CreateBody(m_WorldId, &bodyDef);

	b2ChainDef shape = b2DefaultChainDef();
	shape.points = chain.data();
	shape.count  = chain.size();
	shape.isLoop = false;

	b2CreateChain(body, &shape);
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform = getTransform();
	states.texture   = &m_TilemapTexture;

	target.draw(m_Vertices, states);
}
