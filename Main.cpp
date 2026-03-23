#include "DataHandler.h"
#include "DataHandlingConstants.h"
#include "GraphicsAttributes.h"
#include <memory>
#include <iostream>
#include "TilemapAttributes.h"

int main()
{
	//GameEngine engine;

	//engine.run();
	
	DataHandler<GraphicsAttributes> graphicsDatahandler(DataHandlingConstants::FilepathGraphicsAttributes);

	auto graph = graphicsDatahandler.getById(2);
	auto graph2 = graphicsDatahandler.getById(1);

	std::cout << graph->ImageId;

	DataHandler<TilemapAttributes> tilemapDatahandler("./maps/01/map.json");
	
	std::cout << tilemapDatahandler.getById(0); 

	return 0;
}