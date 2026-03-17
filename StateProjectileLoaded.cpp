#include <SFML/System/Vector2.hpp>
#include "StateProjectileLoaded.h"
#include <box2d.h>
#include "Projectile.h"

void StateProjectileLoaded::enter(Projectile& projectile)
{
	if (!b2Body_IsValid(projectile.m_BodyId))
	{
		return;
	}
	b2Body_Disable(projectile.m_BodyId);
}

void StateProjectileLoaded::exit(Projectile& projectile)
{
}

void StateProjectileLoaded::update(Projectile& projectile, float delta)
{
	projectile.getPosition() = projectile.m_SlingshotBeakPosition;
}
