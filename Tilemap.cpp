#include "Tilemap.h"

#include <math_functions.h>
#include <id.h>
#include <box2d.h>
#include <types.h>

#include <vector>
#include <memory>
#include <algorithm>
#include <map>
#include <utility>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "TilemapAttributes.h"
#include "Tile.h"
#include "Layer.h"
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

			m_TileGridCoordinates.insert({ tile.GridPosition.x, tile.GridPosition.y });

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

std::map<std::pair<float, float>, std::pair<float, float>> Tilemap::getVerticesOutline()
{
	float tileSizeMeters = converter::pixelsToMeters(m_Attributes->TileSize);
	
	std::map<std::pair<float, float>, std::pair<float, float>> outline;
	for (auto& layer : m_Attributes->Layers)
	{
		if (!layer.Collider)
		{
			continue;
		}
		for (auto& tile : layer.Tiles)
		{
			float x = tile.GridPosition.x * tileSizeMeters + converter::pixelsToMeters(getPosition().x);
			float y = tile.GridPosition.y * tileSizeMeters + converter::pixelsToMeters(getPosition().y);

			int gx = tile.GridPosition.x;
			int gy = tile.GridPosition.y;

			sf::RectangleShape shape;
			shape.setFillColor(sf::Color(255, 255, 0, 150));

			float xP = converter::metersToPixels(x);
			float yP = converter::metersToPixels(y);

			float sP = m_Attributes->TileSize;

			if (!m_TileGridCoordinates.contains({ gx, gy - 1 }))
			{
				outline[{ x, y }] = { x + tileSizeMeters, y };

				shape.setPosition({ xP, yP });
				shape.setSize({ sP, 5 });
				m_CollisionDebugLines.push_back(shape);
			}
			if (!m_TileGridCoordinates.contains({ gx, gy + 1 }))
			{
				outline[{ x + tileSizeMeters, y + tileSizeMeters }] = { x, y + tileSizeMeters };

				shape.setPosition({ xP, yP + sP });
				shape.setSize({ sP, 5 });
				m_CollisionDebugLines.push_back(shape);
			}
			if (!m_TileGridCoordinates.contains({ gx - 1, gy }))
			{
				outline[{ x, y + tileSizeMeters }] = { x, y };

				shape.setPosition({ xP, yP });
				shape.setSize({ 5, sP });
				m_CollisionDebugLines.push_back(shape);
			}
			if (!m_TileGridCoordinates.contains({ gx + 1, gy }))
			{
				outline[{ x + tileSizeMeters, y }] = { x + tileSizeMeters, y + tileSizeMeters };

				shape.setPosition({ xP + sP, yP });
				shape.setSize({ 5, sP });
				m_CollisionDebugLines.push_back(shape);
			}
		}
	}

	return outline;
}

std::vector<std::vector<b2Vec2>> Tilemap::getCollisionLoops()
{
	std::vector<std::vector<b2Vec2>> loops;

	auto outline = getVerticesOutline();

	while (!outline.empty())
	{
		std::pair<float, float> startingPoint = outline.begin()->first;
		std::pair<float, float> currentPoint  = startingPoint;

		std::vector<b2Vec2> loop;

		do 
		{
			loop.push_back({ currentPoint.first, currentPoint.second });

			std::pair<float, float> nextPoint = outline[currentPoint];
			outline.erase(currentPoint);
			currentPoint = nextPoint;

		} while (currentPoint != startingPoint);

		loops.push_back(loop);
	}

	return loops;
}

Tilemap::Tilemap(sf::Texture& tilemapTexture, std::shared_ptr<TilemapAttributes> attributes, b2WorldId worldId, sf::Vector2f position) : m_TilemapTexture(tilemapTexture), m_Attributes(attributes), m_WorldId(worldId)
{
	setPosition(position);

	m_Vertices.setPrimitiveType(sf::PrimitiveType::Triangles);

	std::sort(m_Attributes->Layers.begin(), m_Attributes->Layers.end(), std::greater<Layer>());

	updateVertices();
}

void Tilemap::createCollision()
{
	std::vector<std::vector<b2Vec2>> loops = getCollisionLoops();

	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_staticBody;

	b2BodyId body = b2CreateBody(m_WorldId, &bodyDef);

	b2ChainDef shape = b2DefaultChainDef();
	for (auto& loop : loops)
	{		
		shape.points = loop.data();
		shape.count  = loop.size();
		shape.isLoop = false;

		b2CreateChain(body, &shape);
	}
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform = getTransform();
	states.texture   = &m_TilemapTexture;

	target.draw(m_Vertices, states);

	for (auto& shape : m_CollisionDebugLines)
	{
		target.draw(shape);
	}
}
