#include "Projectile.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "BitmapStore.h"
#include "ProjectileAttributes.h"
#include <box2d.h>
#include "Converter.h"
#include <math_functions.h>
#include <SFML/System/Vector2.hpp>
#include <id.h>
#include "PhysicsObject.h"
#include "StateProjectileLaunched.h"
#include <iostream>
#include <format>
#include <memory>
#include <SFML/System/Angle.hpp>
#include "StateProjectileLoaded.h"

Projectile::Projectile(BitmapStore& store, b2WorldId worldId, b2BodyId body, std::shared_ptr<ProjectileAttributes> attributes) :
	IPhysicsObject(worldId),
	m_AnimatedGraphics(store, attributes->Graphics),
	m_ProjectileAttributes(attributes),
	m_BitmapStore(store)
{
	m_BodyId = body;	
	m_Position = converter::metersToPixels(b2Body_GetPosition(body));

	m_AnimatedGraphics.setOriginToCenter();	
}

const ProjectileAttributes* Projectile::getAttributes() const
{
	return m_ProjectileAttributes.get();
}

void Projectile::launch(float slingShotImpulseRatio, sf::Vector2f normalizedDirection)
{
#ifdef _DEBUG
	std::cout << std::format("Launching projectile: impulse ratio [{}], direction [{}, {}]", slingShotImpulseRatio, normalizedDirection.x, normalizedDirection.y);
#endif // _DEBUG

	b2Body_SetTransform(m_BodyId, converter::pixelsToMeters(m_Position), b2Rot_identity);

	normalizedDirection *= -1.0f;

	m_CurrentState = std::make_unique<StateProjectileLaunched>(slingShotImpulseRatio, normalizedDirection, m_BodyId);
	m_CurrentState->enter(*this);
}

void Projectile::disableBody()
{
	b2Body_Disable(m_BodyId);
}

void Projectile::load()
{
	m_CurrentState = std::make_unique<StateProjectileLoaded>();
	m_CurrentState->enter(*this);
}

bool Projectile::isLoaded() const
{
	if (!m_CurrentState)
	{
		return false;
	}
	return typeid(*m_CurrentState) == typeid(StateProjectileLoaded);
}

void Projectile::setRotation(sf::Angle rotation)
{
	m_AnimatedGraphics.setRotation(rotation);
}

sf::Vector2f Projectile::getSlingshotBeakPosition() const
{
	return m_SlingshotBeakPosition;
}

void Projectile::setSlingShotBeakPosition(sf::Vector2f toPosition)
{
	m_SlingshotBeakPosition = toPosition;
}

void Projectile::update(float delta)
{
	if (m_CurrentState) 
	{
		m_CurrentState->update(*this, delta);
	}
	m_AnimatedGraphics.update(delta);

	if (b2Body_IsEnabled(m_BodyId))
	{
		m_Position = converter::metersToPixels(b2Body_GetPosition(m_BodyId));

		m_AnimatedGraphics.setRotation(converter::rotToAngle(b2Body_GetRotation(m_BodyId)));
	}

	m_AnimatedGraphics.setPosition(m_Position);
}

void Projectile::render(sf::RenderTarget& target)
{
	m_AnimatedGraphics.render(target);
}