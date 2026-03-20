#include "ProjectileAttributesDataHandler.h"
#include "ProjectileId.h"
#include <fstream>
#include "DataHandlingConstants.h"

json ProjectileAttributesDataHandler::getDefaultJsonForId(int id)
{

    return data;
}

void ProjectileAttributesDataHandler::createTemplateJsonFile(ProjectileId id)
{
	std::ifstream inputFile(DataHandlingConstants::FilepathProjectileAttributes);
	json data = json::parse(inputFile);

    if (!data.empty())
    {
        return;
    }

    for (int i = static_cast<int>(ProjectileId::Start) + 1; i < static_cast<int>(ProjectileId::End); i++)
    {
        
    }
}
