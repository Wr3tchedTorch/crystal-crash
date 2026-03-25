#include "LevelManager.h"

#include <id.h>

#include <format>
#include <memory>

#include "DataHandler.h"
#include "TilemapAttributes.h"
#include "World.h"
#include "BitmapStore.h"
#include "WorldData.h"
#include "DataHandlerManager.h"
#include "ProjectilesFactory.h"

LevelManager::LevelManager(BitmapStore& store, std::shared_ptr<ProjectilesFactory> projectileFactory, DataHandlerManager& dataManager) :
	m_BitmapStore(store),
	m_ProjectileFactory(projectileFactory),
	m_DataHandler(dataManager)	
{
}

std::unique_ptr<World> LevelManager::loadLevel(int index, b2WorldId worldId)
{
	std::shared_ptr<WorldData> worldData = m_DataHandler.WorldDataHandler->getById(index);

	DataHandler<TilemapAttributes> tilemapDataHandler(std::format("./maps/{}/map.json", index));
	worldData->setTilemapAttributes(tilemapDataHandler.getById(1));

	worldData->SlingshotData.loadProjectileAttributes(*m_DataHandler.ProjectileDataHandler.get());

	return std::make_unique<World>(m_BitmapStore, worldData, m_ProjectileFactory, m_DataHandler, worldId);
}
