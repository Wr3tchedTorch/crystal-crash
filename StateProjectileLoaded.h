#pragma once
#include "IState.h"
#include "Slingshot.h"
#include <SFML/System/Vector2.hpp>

class StateProjectileLoaded : public IState
{
private:
	sf::Vector2f& m_Position;
	Slingshot&	  m_SlingShot;

public:
	void init(sf::Vector2f& position, Slingshot& slingShot);
};
