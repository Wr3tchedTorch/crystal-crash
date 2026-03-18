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
#include "ProjectileStates.h"
#include <iostream>
#include <format>
#include <memory>
#include <utility>
#include <types.h>

Projectile::Projectile(BitmapStore& store, b2WorldId worldId, b2BodyId body, std::shared_ptr<ProjectileAttributes> attributes) :
	IPhysicsObject(worldId),
	m_GraphicsComponent(store, attributes->Graphics),
	m_ProjectileAttributes(attributes),
	m_BitmapStore(store)
{
	m_BodyId = body;	

	m_GraphicsComponent.setOriginToCenter();

	m_CurrentState = &ProjectileStates::Loaded;

	m_CurrentState->enter(*this);
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

	m_CurrentState = new StateProjectileLaunched(slingShotImpulseRatio, normalizedDirection, m_BodyId);
	m_CurrentState->enter(*this);
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
	m_CurrentState->update(*this, delta);
	m_GraphicsComponent.update(delta);

	if (b2Body_IsEnabled(m_BodyId))
	{
		m_Position = converter::metersToPixels(b2Body_GetPosition(m_BodyId));

		m_GraphicsComponent.setRotation(converter::rotToAngle(b2Body_GetRotation(m_BodyId)));
	}

	m_GraphicsComponent.setPosition(m_Position);
}

void Projectile::render(sf::RenderTarget& target)
{
	m_GraphicsComponent.render(target);
}

std::unique_ptr<Projectile> Projectile::clone()
{
	b2BodyId bodyId = b2CreateBody(m_WorldId, m_ProjectileAttributes->Physics.BodyDefinition.get());

	m_ProjectileAttributes->Shape->createShape(bodyId, *m_ProjectileAttributes->Physics.ShapeDefinition.get());

	return std::make_unique<Projectile>(m_BitmapStore, m_WorldId, bodyId, m_ProjectileAttributes);
}