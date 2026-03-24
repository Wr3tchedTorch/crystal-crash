#pragma once
#include <nlohmann/json.hpp>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "ProjectileAttributes.h"
#include <memory>
#include "DataHandler.h"

using json = nlohmann::json;

struct SlingshotData
{
	sf::Vector2f Position;
	std::vector<int> LoadedProjectileIds;

	std::vector<std::shared_ptr<ProjectileAttributes>> getProjectileAttributes()
	{
		return ProjectileAttributes;
	}

	void loadProjectileAttributes(DataHandler<ProjectileAttributes>& handler)
	{
		ProjectileAttributes.resize(LoadedProjectileIds.size());
		for (int i = 0; i < LoadedProjectileIds.size(); ++i)
		{
			ProjectileAttributes[i] = handler.getById(LoadedProjectileIds[i]);
		}
	}

private:
	std::vector<std::shared_ptr<ProjectileAttributes>> ProjectileAttributes;
};

inline void to_json(json& j, const SlingshotData& pa)
{
	j =
	{
		{"ammunition", pa.LoadedProjectileIds},
		{
			"position",
			{
				{"x", pa.Position.x},
				{"y", pa.Position.y}
			}
		}
	};
}

inline void from_json(const json& j, SlingshotData& pa)
{
	j.at("ammunition").get_to(pa.LoadedProjectileIds);

	pa.Position.x = j.at("position").at("x").get<float>();
	pa.Position.y = j.at("position").at("y").get<float>();
}