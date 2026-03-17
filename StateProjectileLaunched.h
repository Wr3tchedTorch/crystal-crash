#pragma once
#include "IProjectileState.h"
#include "Projectile.h"

class StateProjectileLaunched : public IProjectileState
{
private:
	float m_Impulse;

public:
	StateProjectileLaunched(float slingShotImpulse);

	void enter(Projectile& projectile) override;
	void exit(Projectile& projectile) override;
	void update(Projectile& projectile, float delta) override;
};

