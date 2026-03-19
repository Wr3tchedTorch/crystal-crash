#pragma once
#include "ISlingshotState.h"
#include <memory>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "Slingshot.h"

class StateSlingshotLoading : public ISlingshotState
{
private:
	sf::Vector2f m_Direction;
	sf::Vector2f m_BeakPosition;

	sf::FloatRect createTrigger();
	void loadNextProjectile(Slingshot& slingshot);
	bool playProjectileLoadingAnimation(Slingshot& slingshot, float delta);

public:
	void enter(Slingshot& slingshot) override;
	void exit(Slingshot& slingshot) override;
	std::unique_ptr<ISlingshotState> update(Slingshot& slingshot, float delta) override;
};

