#include "Projectile.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "BitmapStore.h"
#include "ProjectileAttributes.h"
#include "AnimatedGraphicsAttributes.h"
#include <box2d.h>
#include <types.h>
#include <collision.h>
#include "Converter.h"
#include <math_functions.h>
#include <SFML/System/Vector2.hpp>
#include <id.h>
#include "PhysicsObject.h"

void Projectile::createPhysicsBody()
{
	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = {2, 2};
	bodyDef.isBullet = false;
	bodyDef.userData = this;
	bodyDef.gravityScale = 2.0f;
	bodyDef.linearDamping = 0.05f;
	bodyDef.enableSleep = true;

	m_BodyId = b2CreateBody(m_WorldId, &bodyDef);

	b2ShapeDef shapeDef = b2DefaultShapeDef();
	shapeDef.density = 1.0f;
	shapeDef.material.restitution = 0.25f;
	shapeDef.material.friction = 0.3f;
	shapeDef.enableHitEvents = true;

	b2Circle circle{};
	circle.radius = converter::pixelsToMeters(m_GraphicsComponent.getTextureRect().size.x / 2.f);

	b2CreateCircleShape(m_BodyId, &shapeDef, &circle);
}

Projectile::Projectile(BitmapStore& store, b2WorldId worldId) :
	IPhysicsObject(worldId),
	m_GraphicsComponent(store)
{
}

void Projectile::init(ProjectileAttributes attributes, AnimatedGraphicsAttributes animationAttributes)
{
	m_ProjectileAttributes = attributes;

	m_GraphicsComponent.init(animationAttributes);
	m_GraphicsComponent.setTexture(attributes.GraphicsAttributes.GraphicsId);
	m_GraphicsComponent.setTextureRect(animationAttributes.TextureRect);

	createPhysicsBody();

	b2Body_SetLinearVelocity(m_BodyId, {4, -2});
}

void Projectile::update(float delta)
{
	m_GraphicsComponent.update(delta);

	sf::Vector2f position = converter::metersToPixels(b2Body_GetPosition(m_BodyId));

	m_GraphicsComponent.setPosition(position);
}

void Projectile::render(sf::RenderTarget& target)
{
	m_GraphicsComponent.render(target);
}
