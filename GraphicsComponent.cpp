#include "GraphicsComponent.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <format>
#include "BitmapStore.h"

GraphicsComponent::GraphicsComponent(BitmapStore& bitmapStore, const std::string& textureId, sf::IntRect textureRect) :
	m_BitmapStore(bitmapStore),
	m_Sprite(m_BitmapStore.getTexture(std::format("graphics/{}", textureId)), textureRect)
{
}

GraphicsComponent::GraphicsComponent(BitmapStore& bitmapStore) : m_BitmapStore(bitmapStore), m_Sprite(m_BitmapStore.getTexture(BitmapStore::PlaceholderGraphicsFilepath))
{
}

void GraphicsComponent::setTexture(const std::string& textureId, sf::IntRect textureRect)
{
	m_Sprite.setTexture(m_BitmapStore.getTexture(std::format("graphics/{}", textureId)));
	m_Sprite.setTextureRect(textureRect);
}

void GraphicsComponent::setPosition(sf::Vector2f position)
{
	m_Sprite.setPosition(position);
}

sf::Vector2f GraphicsComponent::getPosition(sf::Vector2f position)
{
	return m_Sprite.getPosition();
}

void GraphicsComponent::setScale(sf::Vector2f scale)
{
	m_Sprite.setScale(scale);
}

sf::Vector2f GraphicsComponent::getScale(sf::Vector2f position)
{
	return m_Sprite.getScale();
}

sf::FloatRect GraphicsComponent::getGlobalBounds()
{
	return m_Sprite.getGlobalBounds();
}

void GraphicsComponent::update(float delta)
{
}

void GraphicsComponent::render(sf::RenderTarget& target)
{
	target.draw(m_Sprite);
}
