#pragma once

#include <id.h>
#include <math_functions.h>

#include <vector>
#include <memory>
#include <set>
#include <utility>
#include <map>
#include <string>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "TilemapAttributes.h"
#include "DataHandler.h"
#include "TilemapCollisionData.h"

class Tilemap : public sf::Drawable, private sf::Transformable
{
private:
	inline static const int VerticesPerTile = 6;

	sf::VertexArray m_Vertices;
	sf::Texture& m_TilemapTexture;

	std::shared_ptr<TilemapAttributes> m_Attributes;
	std::set<std::pair<int, int>> m_TileGridCoordinates;

	std::vector<sf::RectangleShape> m_CollisionDebugLines;

	std::shared_ptr<DataHandler<TilemapCollisionData>> m_TilemapCollisionDataHandler;

	b2WorldId m_WorldId;

	std::pair<sf::Vector2f, sf::Vector2f> getTileCollisionOutline(sf::Vector2i direction, int tileId);
	void updateVertices();
	std::map<std::pair<float, float>, std::pair<float, float>> getVerticesOutline();
	std::vector<std::vector<b2Vec2>> getCollisionLoops();

public:
	Tilemap(
		sf::Texture& tilemapTexture, 
		std::shared_ptr<TilemapAttributes> attributes, 
		b2WorldId worldId, 
		sf::Vector2f position,
		std::shared_ptr<DataHandler<TilemapCollisionData>> collisionDataHandler
	);

	void createCollision();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

