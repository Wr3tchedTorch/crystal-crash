#include "StateProjectileLaunched.h"
#include "Projectile.h"
#include <box2d.h>

StateProjectileLaunched::StateProjectileLaunched(float slingshotImpulse) : m_Impulse(slingshotImpulse)
{

}


void StateProjectileLaunched::enter(Projectile& projectile)
{
	b2Body_Enable(projectile.m_BodyId);
	//projectile.getAttributes().MaxSpeed

	//b2Body_SetLinearVelocity();
}

void StateProjectileLaunched::exit(Projectile& projectile)
{
}

void StateProjectileLaunched::update(Projectile& projectile, float delta)
{
}
