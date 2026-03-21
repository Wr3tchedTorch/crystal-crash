#include "DataHandler.h"
#include "ProjectileAttributes.h"
#include "DataHandlingConstants.h"
#include "PolygonShapeAttributes.h"
#include "GraphicsAttributes.h"

int main()
{
	//GameEngine engine;

	//engine.run();

	DataHandler<ProjectileAttributes> dataHandler(DataHandlingConstants::FilepathProjectileAttributes);

	DataHandler<GraphicsAttributes> graphicsDatahandler(DataHandlingConstants::FilepathGraphicsAttributes);

	DataHandler<PolygonShapeAttributes> shapeDatahandler(DataHandlingConstants::FilepathShapeAttributes);

	return 0;
}