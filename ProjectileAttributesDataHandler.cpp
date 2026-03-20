#include "ProjectileAttributesDataHandler.h"
#include "ProjectileId.h"
#include <fstream>
#include "DataHandlingConstants.h"
#include "ProjectileAttributes.h"
#include "PolygonShapeAttributes.h"
#include <memory>

json ProjectileAttributesDataHandler::getDefaultJsonForId(int id)
{
    ProjectileAttributes projectile;
    projectile.Id = id;
    projectile.Shape = std::make_shared<PolygonShapeAttributes>();
    return projectile;
}

void ProjectileAttributesDataHandler::createTemplateJsonFile()
{
	std::ifstream inputFile(DataHandlingConstants::FilepathProjectileAttributes);
	json data = json::parse(inputFile);
    inputFile.close();

    if (!data.empty())
    {
        return;
    }

    for (int i = static_cast<int>(ProjectileId::Start) + 1; i < static_cast<int>(ProjectileId::End); i++)
    {
        data += getDefaultJsonForId(i);
    }

    std::ofstream outputFile(DataHandlingConstants::FilepathProjectileAttributes);
    outputFile << data.dump(4);
    outputFile.close();
}

ProjectileAttributesDataHandler::ProjectileAttributesDataHandler()
{
    createTemplateJsonFile();
}

std::shared_ptr<ProjectileAttributes> ProjectileAttributesDataHandler::getById(ProjectileId id)
{
    return std::shared_ptr<ProjectileAttributes>();
}
