#pragma once
#include <memory>
#include "ProjectileAttributes.h"
#include "ProjectileId.h"
#include <unordered_map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ProjectileAttributesDataHandler
{
private:
	std::unordered_map<ProjectileId, std::shared_ptr<ProjectileAttributes>> m_Data;

	json getDefaultJsonForId(int id);
	void createTemplateJsonFile();

public:
	ProjectileAttributesDataHandler();

	std::shared_ptr<ProjectileAttributes> getById(ProjectileId id);
};
