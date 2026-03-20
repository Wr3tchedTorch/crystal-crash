#pragma once
#include <memory>
#include "ProjectileAttributes.h"
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "Projectile.h"

using ordered_json = nlohmann::ordered_json;

class ProjectileAttributesDataHandler
{
private:
	std::unordered_map<Projectile::Id, std::shared_ptr<ProjectileAttributes>> m_Data;

	json getDefaultJsonForId(int id);
	void createTemplateJsonFile();

public:
	ProjectileAttributesDataHandler();

	std::shared_ptr<ProjectileAttributes> getById(Projectile::Id id);
};
