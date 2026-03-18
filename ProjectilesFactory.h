#pragma once
#include "BitmapStore.h"
#include <id.h>
#include "Projectile.h"
#include "ProjectileAttributes.h"
#include "Slingshot.h"
#include <memory>
#include <types.h>

class ProjectilesFactory
{
private:
	BitmapStore& m_BitmapStore;
	b2WorldId    m_WorldId;
	std::shared_ptr<Slingshot> m_Slingshot;

	std::shared_ptr<b2BodyDef>  m_ProjectileBodyDef;
	std::shared_ptr<b2ShapeDef> m_ProjectileShapeDef;

	bool m_Instantiated = false;

public:
	ProjectilesFactory(BitmapStore& store, b2WorldId worldId, std::shared_ptr<Slingshot> slingshot);

	std::unique_ptr<Projectile> createProjectile(ProjectileAttributes attributes);
};

