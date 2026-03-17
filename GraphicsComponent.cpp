#include "GraphicsComponent.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <format>
#include "BitmapStore.h"

bool GraphicsComponent::isTextureRectInvalid(sf::IntRect textureRect)
{
	return textureRect.position.x == 0 && textureRect.position.y == 0 &&
		   textureRect.size.x	  == 0 && textureRect.size.y	 == 0;
}

GraphicsComponent::GraphicsComponent(BitmapStore& bitmapStore, const std::string& textureId, sf::IntRect textureRect) :
	m_BitmapStore(bitmapStore),
	m_Sprite(m_BitmapStore.getTexture(std::format("graphics/{}", textureId)))
{
	sf::Vector2f size = sf::Vector2f(m_BitmapStore.getTexture(std::format("graphics/{}", textureId)).getSize());

	if (!isTextureRectInvalid(textureRect))
	{
		m_Sprite.setTextureRect(textureRect);
		size = sf::Vector2f(textureRect.size);
	}
	m_Sprite.setOrigin({ size.x / 2.0f, size.y / 2.0f });
}

GraphicsComponent::GraphicsComponent(BitmapStore& bitmapStore) : m_BitmapStore(bitmapStore), m_Sprite(m_BitmapStore.getTexture(BitmapStore::PlaceholderGraphicsFilepath))
{
}

void GraphicsComponent::setTexture(const std::string& textureId, sf::IntRect textureRect)
{
	m_Sprite.setTexture(m_BitmapStore.getTexture(std::format("graphics/{}", textureId)));	
	if (!isTextureRectInvalid(textureRect))
	{
		m_Sprite.setTextureRect(textureRect);
		m_Sprite.setOrigin({ textureRect.size.x/2.0f, textureRect.size.y/2.0f });
	}
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

sf::IntRect GraphicsComponent::getTextureRect()
{
	return m_Sprite.getTextureRect();
}

void GraphicsComponent::update(float delta)
{
}

void GraphicsComponent::render(sf::RenderTarget& target)
{
	target.draw(m_Sprite);
}
