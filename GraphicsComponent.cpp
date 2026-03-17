#include "GraphicsComponent.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <format>
#include "BitmapStore.h"
#include <SFML/System/Angle.hpp>
#include <SFML/Graphics/Texture.hpp>

bool GraphicsComponent::isTextureRectValid(sf::IntRect textureRect)
{
	return textureRect.size.x != 0 &&
		   textureRect.size.y != 0;
}

void GraphicsComponent::setOriginToCenter()
{
	sf::Vector2f size = sf::Vector2f(m_Sprite.getTextureRect().size);

	m_Sprite.setOrigin({ size.x / 2.0f, size.y / 2.0f });
}

GraphicsComponent::GraphicsComponent(BitmapStore& bitmapStore, const std::string& textureId, sf::IntRect textureRect) :
	m_BitmapStore(bitmapStore),
	m_Sprite(m_BitmapStore.getTexture(std::format("graphics/{}", textureId)))
{
	if (isTextureRectValid(textureRect))
	{
		m_Sprite.setTextureRect(textureRect);
	}
	setOriginToCenter();
}

GraphicsComponent::GraphicsComponent(BitmapStore& bitmapStore, const std::string& textureId, bool tiled) : m_BitmapStore(bitmapStore), m_Sprite(m_BitmapStore.getTexture(BitmapStore::PlaceholderGraphicsFilepath))
{
	sf::Texture& texture = m_BitmapStore.getTexture(std::format("graphics/{}", textureId));
	texture.setRepeated(tiled);	
	setTexture(textureId);
}

GraphicsComponent::GraphicsComponent(BitmapStore& bitmapStore) : m_BitmapStore(bitmapStore), m_Sprite(m_BitmapStore.getTexture(BitmapStore::PlaceholderGraphicsFilepath))
{
}

void GraphicsComponent::setTexture(const std::string& textureId)
{
	m_Sprite.setTexture(m_BitmapStore.getTexture(std::format("graphics/{}", textureId)), true);
	setOriginToCenter();
}

void GraphicsComponent::setTextureRect(sf::IntRect textureRect)
{
	if (isTextureRectValid(textureRect))
	{
		m_Sprite.setTextureRect(textureRect);
		setOriginToCenter();
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

void GraphicsComponent::setRotation(sf::Angle angle)
{
	m_Sprite.setRotation(angle);
}

sf::Angle GraphicsComponent::getRotation()
{
	return m_Sprite.getRotation();
}

void GraphicsComponent::update(float delta)
{
}

void GraphicsComponent::render(sf::RenderTarget& target)
{
	target.draw(m_Sprite);
}
