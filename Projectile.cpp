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
#include "StateProjectileLaunched.h"
#include "ProjectileStates.h"
#include <iostream>
#include <format>
#include "GraphicsAttributes.h"
#include <utility>
#include <memory>

Projectile::Projectile(BitmapStore& store, b2WorldId worldId) :
	IPhysicsObject(worldId),
	m_GraphicsComponent(store)
{	
	m_CurrentState = nullptr;
	m_SlingshotBeakPosition = nullptr;
}

const std::shared_ptr<ProjectileAttributes> Projectile::getAttributes() const
{
	return m_ProjectileAttributes;
}

void Projectile::init(std::shared_ptr<ProjectileAttributes> attributes, std::shared_ptr<GraphicsAttributes> animationAttributes, sf::Vector2f& slingshotBeakPosition, b2BodyId body)
{
	m_BodyId = body;

	m_SlingshotBeakPosition = &slingshotBeakPosition;

	m_ProjectileAttributes = attributes;

	m_GraphicsComponent.init(animationAttributes);
	m_GraphicsComponent.setTexture(attributes->Graphics.GraphicsId);
	m_GraphicsComponent.setTextureRect(animationAttributes->TextureRect);
	m_GraphicsComponent.setScale({ 1.0f, 1.0f });
	m_GraphicsComponent.setOriginToCenter();

	m_CurrentState = &ProjectileStates::Loaded;

	m_CurrentState->enter(*this);
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
