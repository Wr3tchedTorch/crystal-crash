#include "DataHandlerStore.h"
#include <memory>
#include "DataHandler.h"
#include "WorldData.h"
#include "DataHandlingConstants.h"
#include "ProjectileAttributes.h"

DataHandler<WorldData>& DataHandlerStore::getWorldDataHandler()
{
	if (!m_WorldDataHandler)
	{
		m_WorldDataHandler = std::make_unique<DataHandler<WorldData>>(DataHandlingConstants::FilepathWorldData);
	}
	return *m_WorldDataHandler.get();
}

DataHandler<ProjectileAttributes>& DataHandlerStore::getProjectileDataHandler()
{
	if (!m_ProjectileDataHandler)
	{
		m_ProjectileDataHandler = std::make_unique<DataHandler<ProjectileAttributes>>(DataHandlingConstants::FilepathProjectileAttributes);
	}
	return *m_ProjectileDataHandler.get();
}
