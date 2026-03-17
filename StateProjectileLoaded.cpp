#include <id.h>
#include <SFML/System/Vector2.hpp>
#include "StateProjectileLoaded.h"
#include <box2d.h>

void StateProjectileLoaded::init(b2BodyId body, sf::Vector2f& parentPosition, sf::Vector2f& slingshotPosition)
{
	m_ParentBodyId   = body;
	m_ParentPosition = &parentPosition;
	m_SlingshotBeakPosition = &slingshotPosition;
}

void StateProjectileLoaded::enter()
{
	if (!b2Body_IsValid(m_ParentBodyId))
	{
		return;
	}
	b2Body_Disable(m_ParentBodyId);
}

void StateProjectileLoaded::exit()
{
	b2Body_Enable(m_ParentBodyId);
}

void StateProjectileLoaded::update(float delta)
{
	if (!m_ParentPosition || !m_SlingshotBeakPosition)
	{
		return;
	}
	*m_ParentPosition = *m_SlingshotBeakPosition;
}
