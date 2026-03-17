#pragma once
#include "IComponent.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <string>
#include "BitmapStore.h"
#include <SFML/System/Angle.hpp>

class GraphicsComponent : public IComponent
{

private:
	BitmapStore& m_BitmapStore;

protected:
	sf::Sprite m_Sprite;
	
	bool isTextureRectValid(sf::IntRect textureRect);

public:
	GraphicsComponent(BitmapStore& bitmapStore, const std::string& textureId, sf::IntRect textureRect);
	GraphicsComponent(BitmapStore& bitmapStore, const std::string& textureId, bool tiled = false);
	GraphicsComponent(BitmapStore& bitmapStore);

	void setTexture(const std::string& textureId);
	void setTextureRect(sf::IntRect textureRect);

	void setOriginToCenter();
	void setOriginToTopCenter();

	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();

	void setScale(sf::Vector2f position);
	sf::Vector2f getScale();

	sf::IntRect getTextureRect();

	void setRotation(sf::Angle angle);
	sf::Angle getRotation();

	virtual void update(float delta) override;
	virtual void render(sf::RenderTarget& target) override;
};

 