#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

class IGameObject
{
private:
	sf::Vector2f m_Position;

public:
	virtual void update(float delta) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};

