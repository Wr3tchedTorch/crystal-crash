#pragma once
#include "IState.h"
#include "Slingshot.h"
#include <SFML/System/Vector2.hpp>
#include <id.h>

class StateProjectileLoaded : public IState
{
private:
	b2BodyId m_ParentBodyId;
	sf::Vector2f* m_ParentPosition;
	sf::Vector2f* m_SlingshotBeakPosition;

public:
	void init(b2BodyId body, sf::Vector2f& parentPosition, sf::Vector2f& slingshotPosition);

	void enter() override;
	void exit() override;
	void update(float delta) override;
};
