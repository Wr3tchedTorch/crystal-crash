#include "StateProjectileLaunched.h"
#include "Projectile.h"
#include <box2d.h>
#include <SFML/System/Vector2.hpp>
#include <math_functions.h>
#include <id.h>

StateProjectileLaunched::StateProjectileLaunched(float slingshotImpulseRatio, sf::Vector2f normalizedDirection, b2BodyId bodyId) : m_ImpulseRatio(slingshotImpulseRatio), m_NormalizedDirection(normalizedDirection)
{
	b2Body_Enable(bodyId);
}

void StateProjectileLaunched::enter(Projectile& projectile)
{
	b2Vec2 velocity = {
		m_NormalizedDirection.x,
		m_NormalizedDirection.y
	};
	velocity *= projectile.getAttributes().MaxSpeed * m_ImpulseRatio;

	b2Body_SetLinearVelocity(projectile.m_BodyId, velocity);
}


void StateProjectileLaunched::exit(Projectile& projectile)
{
}

void StateProjectileLaunched::update(Projectile& projectile, float delta)
{
}
