#include "GraphicsComponent.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

GraphicsComponent::GraphicsComponent(sf::Texture& texture, sf::IntRect textureRect) : m_Sprite(texture, textureRect)
{
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
