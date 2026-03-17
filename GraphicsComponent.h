#pragma once
#include "IComponent.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <string>
#include "BitmapStore.h"

class GraphicsComponent : public IComponent
{

private:
	BitmapStore& m_BitmapStore;

protected:
	sf::Sprite m_Sprite;

public:
	GraphicsComponent(BitmapStore& bitmapStore, const std::string& textureId, sf::IntRect textureRect);
	GraphicsComponent(BitmapStore& bitmapStore);

	void setTexture(const std::string& textureId, sf::IntRect textureRect);

	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition(sf::Vector2f position);

	void setScale(sf::Vector2f position);
	sf::Vector2f getScale(sf::Vector2f position);

	sf::IntRect getTextureRect();

	virtual void update(float delta) override;
	virtual void render(sf::RenderTarget& target) override;
};

 