#include "DataHandler.h"
#include "ProjectileAttributes.h"
#include "DataHandlingConstants.h"
#include <iostream>
#include <memory>

int main()
{
	//GameEngine engine;

	//engine.run();

	DataHandler<ProjectileAttributes> dataHandler(DataHandlingConstants::FilepathProjectileAttributes);

	return 0;
}