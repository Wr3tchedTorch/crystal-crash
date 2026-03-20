#include "ProjectileAttributesDataHandler.h"
#include "Projectile.h"
#include <fstream>
#include "DataHandlingConstants.h"
#include "ProjectileAttributes.h"
#include "PolygonShapeAttributes.h"
#include <memory>
#include "InputFileHelper.h"

json ProjectileAttributesDataHandler::getDefaultJsonForId(int id)
{
    ProjectileAttributes projectile;
    projectile.Id    = id;
    projectile.Name  = Projectile::toString(static_cast<Projectile::Id>(id));
    projectile.Shape = std::make_shared<PolygonShapeAttributes>();
    return projectile;
}

void ProjectileAttributesDataHandler::createTemplateJsonFile()
{
    std::ifstream inputFile(DataHandlingConstants::FilepathProjectileAttributes);

    if (!InputFileHelper::is_empty(inputFile))
    {
        return;
    }
    inputFile.close();

    json data;

    for (int i = static_cast<int>(Projectile::Id::Start) + 1; i < static_cast<int>(Projectile::Id::End); i++)
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

std::shared_ptr<ProjectileAttributes> ProjectileAttributesDataHandler::getById(Projectile::Id id)
{
    return std::shared_ptr<ProjectileAttributes>();
}
