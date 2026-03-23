#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

class IGameObject
{
protected:
	sf::Vector2f m_Position;

public:
	std::string m_Id;

	virtual void update(float delta) = 0;
	virtual void render(sf::RenderTarget& target) = 0;

	sf::Vector2f& getPosition() { return m_Position; };
};

