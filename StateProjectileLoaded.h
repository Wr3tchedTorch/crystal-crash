#pragma once
#include "IProjectileState.h"

class Projectile;

class StateProjectileLoaded : public IProjectileState
{
public:
	void enter(Projectile& projectile) override;
	void exit(Projectile& projectile)  override;
	void update(Projectile& projectile, float delta) override;
};
