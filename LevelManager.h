#pragma once

#include <memory>

#include "World.h"
#include "BitmapStore.h"
#include "ProjectilesFactory.h"
#include "DataHandlerManager.h"

class LevelManager
{
private:
	std::shared_ptr<ProjectilesFactory> m_ProjectileFactory;

	DataHandlerManager& m_DataHandler;
	BitmapStore& m_BitmapStore;

public:	
	LevelManager(BitmapStore& store, std::shared_ptr<ProjectilesFactory> projectileFactory, DataHandlerManager& dataManager);
	std::unique_ptr<World> loadLevel(int index);
};

