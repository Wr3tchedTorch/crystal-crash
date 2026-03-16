#pragma once
#include "GameObject.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <id.h>

class PhysicsObject : public GameObject
{
private:
	b2BodyId  m_BodyId;
	b2WorldId m_WorldId;
	sf::Vector2f m_Velocity;

public:
	virtual void update(float delta) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};

