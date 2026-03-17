#pragma once
#include "IGameObject.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <id.h>

class IPhysicsObject : public IGameObject
{
protected:
	b2BodyId  m_BodyId;
	b2WorldId m_WorldId;

public:
	IPhysicsObject(b2WorldId worldId);

	virtual void update(float delta) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};

