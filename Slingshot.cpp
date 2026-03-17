#include "Slingshot.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <SFML/System/Angle.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "BitmapStore.h"
#include "DragSystem.h"
#include "GameEngine.h"
#include "Projectile.h"

const std::string Slingshot::BaseGraphicsId  = "Lamp Post 1 TALL - Silver.png";
const std::string Slingshot::ChainGraphicsId = "Chain - Bronze.png";
const sf::Vector2f Slingshot::ChainGraphicsSize = { 7.0f, 53.0f };
const float Slingshot::MaxDragDistance = 200;

Slingshot::Slingshot(BitmapStore& store, sf::Vector2f position) :
	m_BaseGraphicsComponent(store, BaseGraphicsId),
	m_ChainGraphicsComponent(store, ChainGraphicsId, true)
{
	m_BaseGraphicsComponent.setOriginToCenter();
	m_BaseGraphicsComponent.setPosition(position);

	sf::Vector2f chainPosition(position);
	chainPosition.y -= m_BaseGraphicsComponent.getTextureRect().size.y/2.0f;

	m_ChainGraphicsComponent.setPosition(chainPosition);
	m_ChainGraphicsComponent.setOriginToTopCenter();
}

sf::Vector2f& Slingshot::getBeakPosition()
{
	float length = std::min(DragSystem::get().getDragDistance(), MaxDragDistance);
	length = std::abs(length);

	m_BeakPosition  = m_ChainGraphicsComponent.getPosition();
	m_BeakPosition += DragSystem::get().getDragDirection() * length;

	return m_BeakPosition;
}

void Slingshot::loadProjectile(Projectile* projectile)
{
	m_LoadedProjectiles.push(projectile);
}

void Slingshot::updateChainLength()
{
	float length = std::min(DragSystem::get().getDragDistance(), MaxDragDistance);
	length = std::abs(length);

	sf::IntRect textureRect;
	textureRect.position = { 0, 0 };
	textureRect.size = {
		static_cast<int>(ChainGraphicsSize.x), 
		static_cast<int>(length)
	};
	m_ChainGraphicsComponent.setTextureRect(textureRect);
}

void Slingshot::updateChainRotation()
{
	sf::Angle rot = (GameEngine::MousePositionInGameCoords - DragSystem::get().getDragStartPosition()).angle();
	rot -= sf::degrees(90);

	m_ChainGraphicsComponent.setRotation(rot);
}

void Slingshot::update(float delta)
{	
	if (!DragSystem::get().isDragging())
	{
		m_ChainGraphicsComponent.setTextureRect({ {0, 0}, {0, 0} });
		return;
	}	
	if (m_ChainGraphicsComponent.getPosition().x < GameEngine::MousePositionInGameCoords.x)
	{
		return;
	}
	updateChainLength();
	updateChainRotation();
}

void Slingshot::render(sf::RenderTarget& target)
{
	m_BaseGraphicsComponent.render(target);
	m_ChainGraphicsComponent.render(target);
}
