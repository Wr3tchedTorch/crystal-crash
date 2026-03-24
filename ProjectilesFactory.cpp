#include "ProjectilesFactory.h"

#include <id.h>
#include <types.h>
#include <box2d.h>

#include <cassert>
#include <memory>
#include <vector>
#include <utility>

#include "Converter.h"
#include "ProjectileAttributes.h"
#include "BitmapStore.h"
#include "Slingshot.h"
#include "Projectile.h"

ProjectilesFactory::ProjectilesFactory(BitmapStore& store, b2WorldId worldId) :
	m_BitmapStore(store),
	m_WorldId(worldId)
{
	assert(!m_Instantiated);
	m_Instantiated = true;

	m_ProjectileBodyDef = std::make_shared<b2BodyDef>(b2DefaultBodyDef());
	m_ProjectileBodyDef->type = b2_dynamicBody;
	m_ProjectileBodyDef->isBullet = true;
	m_ProjectileBodyDef->gravityScale = 2.0f;
	m_ProjectileBodyDef->linearDamping = 0.05f;
	m_ProjectileBodyDef->enableSleep = true;	

	m_ProjectileShapeDef = std::make_shared<b2ShapeDef>(b2DefaultShapeDef());
	m_ProjectileShapeDef->density = 10.0f;	
	m_ProjectileShapeDef->material.restitution = 0.25f;
	m_ProjectileShapeDef->material.friction = 0.3f;
	m_ProjectileShapeDef->enableHitEvents = true;
}

std::unique_ptr<Projectile> ProjectilesFactory::createProjectile(std::shared_ptr<ProjectileAttributes> attributes, int projectileOrder, Slingshot& slingshot)
{	
	m_ProjectileBodyDef->position = converter::pixelsToMeters(slingshot.getIdlePosition(projectileOrder));

	b2BodyId bodyId = b2CreateBody(m_WorldId, m_ProjectileBodyDef.get());

	attributes->getGraphics()->getShape()->createShape(bodyId, *m_ProjectileShapeDef);

	return std::make_unique<Projectile>(m_BitmapStore, m_WorldId, bodyId, attributes);
}

std::vector<std::unique_ptr<Projectile>> ProjectilesFactory::createProjectiles(std::vector<std::shared_ptr<ProjectileAttributes>> attributes, Slingshot& slingshot)
{
	std::vector<std::unique_ptr<Projectile>> projectiles;

	for (int i = 0; i < attributes.size(); ++i)	
	{
		projectiles.push_back(std::move(createProjectile(attributes[i], i, slingshot)));
	}

	return projectiles;
}
