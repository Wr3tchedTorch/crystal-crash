#include "DataHandler.h"
#include "ProjectileAttributes.h"
#include "DataHandlingConstants.h"
#include "PolygonShapeAttributes.h"
#include "GraphicsAttributes.h"
#include <memory>
#include <math_functions.h>
#include <iostream>



int main()
{
	//GameEngine engine;

	//engine.run();
	
	DataHandler<GraphicsAttributes> graphicsDatahandler(DataHandlingConstants::FilepathGraphicsAttributes);

	auto graph = graphicsDatahandler.getById(2);
	auto graph2 = graphicsDatahandler.getById(1);

	std::cout << graph->ImageId;

	return 0;
}