#pragma once
#include "IProjectileState.h"
#include "Projectile.h"
#include <SFML/System/Vector2.hpp>
#include <id.h>

class StateProjectileLaunched : public IProjectileState
{
private:
	float m_ImpulseRatio;
	sf::Vector2f m_NormalizedDirection;

public:
	StateProjectileLaunched(float slingshotImpulse, sf::Vector2f normalizedDirection, b2BodyId bodyId);

	void enter(Projectile& projectile) override;
	void exit(Projectile& projectile) override;
	void update(Projectile& projectile, float delta) override;
};

