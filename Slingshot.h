#pragma once
#include "IGameObject.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "GraphicsComponent.h"
#include "BitmapStore.h"
#include <SFML/System/Vector2.hpp>
#include <string>

class Slingshot : public IGameObject
{
private:
	GraphicsComponent m_BaseGraphicsComponent;
	//TiledGraphicsComponent m_ChainGraphicsComponent;

public:
	static const std::string BaseGraphicsId;
	static const std::string ChainGraphicsId;

	Slingshot(BitmapStore& store, sf::Vector2f position);
	void update(float delta) override;
	void render(sf::RenderTarget& target) override;
};

