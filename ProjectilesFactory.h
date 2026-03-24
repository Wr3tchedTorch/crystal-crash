#pragma once

#include <id.h>
#include <types.h>

#include <memory>
#include <vector>

#include "BitmapStore.h"
#include "Projectile.h"
#include "ProjectileAttributes.h"
#include "Slingshot.h"
#include "DataHandler.h"

class ProjectilesFactory
{
private:
	BitmapStore& m_BitmapStore;
	b2WorldId    m_WorldId;

	std::shared_ptr<b2BodyDef>  m_ProjectileBodyDef;
	std::shared_ptr<b2ShapeDef> m_ProjectileShapeDef;

	bool m_Instantiated = false;

public:
	ProjectilesFactory(BitmapStore& store, b2WorldId worldId);

	std::unique_ptr<Projectile> createProjectile(std::shared_ptr<ProjectileAttributes> attributes, int order, Slingshot& slingshot);
	std::vector<std::unique_ptr<Projectile>> createProjectiles(std::vector<std::shared_ptr<ProjectileAttributes>> attributes, Slingshot& slingshot);
};

