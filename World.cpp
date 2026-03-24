#include "World.h"

#include <memory>
#include <format>
#include <utility>
#include <vector>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "BitmapStore.h"
#include "IGameObject.h"
#include "WorldData.h"
#include "Tilemap.h"
#include "Slingshot.h"
#include "ProjectilesFactory.h"
#include "Projectile.h"
#include "DataHandler.h"
#include "GraphicsAttributes.h"
#include "PolygonShapeAttributes.h"

World::World(
	BitmapStore& store, 
	std::shared_ptr<WorldData> data, 
	std::shared_ptr<ProjectilesFactory> projectileFactory, 
	std::shared_ptr<DataHandler<GraphicsAttributes>> graphicsDataHandler,
	std::shared_ptr<DataHandler<PolygonShapeAttributes>> shapeDataHandler
) :
	m_WorldData(data),
	m_ProjectileFactory(projectileFactory)	
{
	m_Tilemap = std::make_unique<Tilemap>(store.getTexture(std::format("./maps/{}/spritesheet.png", m_WorldData->TilemapId)), m_WorldData->getTilemapAttributes());

	auto slingshot = std::make_unique<Slingshot>(store, m_WorldData->SlingshotData.Position);

	for (auto& proj : m_WorldData->SlingshotData.getProjectileAttributes())
	{		
		proj->setGraphics(graphicsDataHandler->getById(proj->GraphicsId));
		proj->getGraphics()->setShape(shapeDataHandler->getById(proj->getGraphics()->ShapeId));
	}

	std::vector<std::unique_ptr<Projectile>> projectiles = projectileFactory->createProjectiles(m_WorldData->SlingshotData.getProjectileAttributes(), *slingshot.get());
	for (auto& proj : projectiles)
	{
		slingshot->loadProjectile(std::move(proj));
	}

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
