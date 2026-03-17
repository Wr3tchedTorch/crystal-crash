#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>
#include <vector>

class IScreen
{
protected:
	std::vector<sf::View> m_Views;	

public:	
	virtual void update(float delta) = 0;

	virtual void render(sf::RenderTarget& target) = 0;
};

