#pragma once
#include "Projectile.h"
#include "StateProjectileLoaded.h"

class IProjectileState
{
public:
	static StateProjectileLoaded   StateProjectileLoaded;

	virtual void enter(Projectile& projectile) = 0;
	virtual void exit(Projectile& projectile)  = 0;

	virtual void update(Projectile& projectile, float delta) = 0;
};
