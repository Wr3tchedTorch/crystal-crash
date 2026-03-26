#include "DataHandlerManager.h"

#include <memory>

#include "DataHandler.h"
#include "GraphicsAttributes.h"
#include "ProjectileAttributes.h"
#include "WorldData.h"
#include "PolygonShapeAttributes.h"
#include "DataHandlingConstants.h"
#include "ShapeAttributes.h"
#include "TilemapCollisionData.h"

DataHandlerManager::DataHandlerManager()
{
	WorldDataHandler		= std::make_shared<DataHandler<WorldData>>(DataHandlingConstants::FilepathWorldData);
	ProjectileDataHandler	= std::make_shared<DataHandler<ProjectileAttributes>>(DataHandlingConstants::FilepathProjectileAttributes);
	GraphicsDataHandler		= std::make_shared<DataHandler<GraphicsAttributes>>(DataHandlingConstants::FilepathGraphicsAttributes);
	PolygonShapeDataHandler	= std::make_shared<DataHandler<PolygonShapeAttributes>>(DataHandlingConstants::FilepathShapeAttributes);
	ShapeDataHandler		= std::make_shared<DataHandler<ShapeAttributes>>(DataHandlingConstants::FilepathShapeAttributes);
	TilemapCollisionDataHandler = std::make_shared<DataHandler<TilemapCollisionData>>(DataHandlingConstants::FilepathTilemapCollisionData);
}
