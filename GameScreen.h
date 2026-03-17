#pragma once
#include "IScreen.h"
#include <SFML/Graphics/RenderTarget.hpp>

class GameScreen : public IScreen
{
public:
	GameScreen();
	void update(float delta) override;
	void render(sf::RenderTarget& target) override;
};

