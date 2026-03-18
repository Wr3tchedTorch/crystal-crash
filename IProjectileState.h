#pragma once

class Projectile;

class IProjectileState
{
public:
	virtual void enter(Projectile& projectile) = 0;
	virtual void exit(Projectile& projectile)  = 0;

	virtual void update(Projectile& projectile, float delta) = 0;
};
