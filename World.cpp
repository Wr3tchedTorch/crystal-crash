#include "World.h"

#include <id.h>

#include <memory>
#include <format>
#include <utility>
#include <vector>
#include <string>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

#include "BitmapStore.h"
#include "IGameObject.h"
#include "WorldData.h"
#include "Tilemap.h"
#include "Slingshot.h"
#include "ProjectilesFactory.h"
#include "Projectile.h"
#include "GraphicsAttributes.h"
#include "DataHandlerManager.h"
#include "ShapeAttributes.h"
#include "ProjectileAttributes.h"
#include "GameEngine.h"

void World::initializeProjectiles(DataHandlerManager& handlerManager)
{
	for (auto& proj : m_WorldData->SlingshotData.getProjectileAttributes())
	{
		proj->setGraphics(handlerManager.GraphicsDataHandler->getById(proj->GraphicsId));

		int shapeId = proj->getGraphics()->ShapeId;

		std::shared_ptr<ShapeAttributes> shape = handlerManager.ShapeDataHandler->getById(shapeId);
		std::string shapeType = shape->typeToString(shape->Type);

		proj->getGraphics()->setShape(handlerManager.getShapeAttributes(shapeType, shapeId));
	}
}

void World::reloadSlingshot(std::vector<std::shared_ptr<ProjectileAttributes>> projectileAttributes, Slingshot& slingshot, std::shared_ptr<ProjectilesFactory> projectileFactory)
{
	std::vector<std::unique_ptr<Projectile>> projectiles = projectileFactory->createProjectiles(m_WorldData->SlingshotData.getProjectileAttributes(), slingshot);
	for (auto& proj : projectiles)
	{
		slingshot.loadProjectile(std::move(proj));
	}
}

World::World(
	BitmapStore& store, 
	std::shared_ptr<WorldData> data, 
	std::shared_ptr<ProjectilesFactory> projectileFactory,	
	DataHandlerManager& handlerManager,
	b2WorldId worldId
) :
	m_WorldData(data),
	m_ProjectileFactory(projectileFactory)	
{
	sf::Vector2f mapSize(
		{
			static_cast<float>(m_WorldData->getTilemapAttributes()->MapWidth)  * m_WorldData->getTilemapAttributes()->TileSize,
			static_cast<float>(m_WorldData->getTilemapAttributes()->MapHeight) * m_WorldData->getTilemapAttributes()->TileSize
		}
	);

	sf::Vector2f tilemapPosition;
	tilemapPosition.x  = mapSize.x / 2.0f;
	tilemapPosition.y  = (GameEngine::Resolution.y / mapSize.y) * mapSize.y;
	tilemapPosition.y -= mapSize.y;
	tilemapPosition.y += m_WorldData->getTilemapAttributes()->TileSize;

	m_Tilemap = std::make_unique<Tilemap>(store.getTexture(std::format("./maps/{}/spritesheet.png", m_WorldData->TilemapId)), m_WorldData->getTilemapAttributes(), worldId, tilemapPosition);

	GameEngine::Resolution;

	initializeProjectiles(handlerManager);

	auto slingshot = std::make_unique<Slingshot>(store, m_WorldData->SlingshotData.Position);

	reloadSlingshot(m_WorldData->SlingshotData.getProjectileAttributes(), *slingshot.get(), projectileFactory);

	m_Entities.push_back(std::move(slingshot));
}

void World::update(float delta)
{
	for (auto& entity : m_Entities)
	{
		entity->update(delta);
	}
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& entity : m_Entities)
	{
		entity->render(target);
	}
	target.draw(*m_Tilemap.get());
}
