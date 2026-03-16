#pragma once
#include "Screen.h"
#include <SFML/Graphics/RenderTarget.hpp>

class GameScreen : public Screen
{


public:
	GameScreen();
	void update(float delta) override;
	void render(sf::RenderTarget& target) override;
};

