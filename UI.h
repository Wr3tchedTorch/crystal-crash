#pragma once
#include <SFML/Graphics/RenderTarget.hpp>

class UI
{
public:
	virtual void update(float delta) = 0;

	virtual void render(sf::RenderTarget& target) = 0;
};

