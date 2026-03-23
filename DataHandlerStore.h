#pragma once
#include <memory>
#include "ProjectileAttributes.h"
#include "WorldData.h"
#include "DataHandler.h"

class DataHandlerStore
{
private:
	std::unique_ptr<DataHandler<WorldData>> m_WorldDataHandler;
	std::unique_ptr<DataHandler<ProjectileAttributes>> m_ProjectileDataHandler;

public:

	DataHandler<WorldData>& getWorldDataHandler();
	DataHandler<ProjectileAttributes>& getProjectileDataHandler();
};

