#include "ProjectilesFactory.h"
#include <id.h>
#include <cassert>
#include <memory>
#include <types.h>
#include <box2d.h>
#include "Converter.h"
#include "ProjectileAttributes.h"
#include "BitmapStore.h"
#include "Slingshot.h"
#include "Projectile.h"

ProjectilesFactory::ProjectilesFactory(BitmapStore& store, b2WorldId worldId, std::shared_ptr<Slingshot> slingshot) :
	m_BitmapStore(store),
	m_WorldId(worldId),
	m_Slingshot(slingshot)
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
	m_ProjectileShapeDef->density = 1.0f;
	m_ProjectileShapeDef->material.restitution = 0.25f;
	m_ProjectileShapeDef->material.friction = 0.3f;
	m_ProjectileShapeDef->enableHitEvents = true;
}

std::unique_ptr<Projectile> ProjectilesFactory::createProjectile(ProjectileAttributes attributes)
{	
	m_ProjectileBodyDef->position = converter::pixelsToMeters(m_Slingshot->getNextIdlePosition());

	b2BodyId bodyId = b2CreateBody(m_WorldId, m_ProjectileBodyDef.get());

	attributes.Shape->createShape(bodyId, *m_ProjectileShapeDef.get());

	attributes.Physics.BodyDefinition  = m_ProjectileBodyDef;
	attributes.Physics.ShapeDefinition = m_ProjectileShapeDef;

	return std::make_unique<Projectile>(m_BitmapStore, m_WorldId, bodyId, std::make_shared<ProjectileAttributes>(attributes));
}
