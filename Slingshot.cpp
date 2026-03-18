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
#include <cmath>

const std::string Slingshot::BaseGraphicsId  = "Lamp Post 1 SHORT - Silver.png";
const std::string Slingshot::ChainGraphicsId = "Chain - Bronze.png";
const sf::Vector2f Slingshot::ChainGraphicsSize = { 7.0f, 53.0f };
const float Slingshot::MaxDragDistance = 150;
const float Slingshot::SpaceBetweenIdleProjectiles = 100;

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

sf::Vector2f Slingshot::getNextIdlePosition(int order) const
{
	sf::Vector2f idlePosition(m_Position);
	idlePosition.y += m_BaseGraphicsComponent.getTextureRect().size.y / 2.0f;

	idlePosition.x += order * SpaceBetweenIdleProjectiles;

	return idlePosition;
}

void Slingshot::updateBeakPosition()
{
	float length = std::min(DragSystem::get().getDragDistance(), MaxDragDistance);
	length = std::abs(length);

	m_BeakPosition = m_ChainGraphicsComponent.getPosition();
	m_BeakPosition += DragSystem::get().getDragDirection() * length;

	m_LoadedProjectiles.front()->setSlingShotBeakPosition(m_BeakPosition);
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
	sf::Vector2f direction = DragSystem::get().getDragDirection();
	if (direction.x == 0 && direction.y == 0)
	{
		return;
	}
	sf::Angle rot = direction.angle();
	rot -= sf::degrees(90);

	m_ChainGraphicsComponent.setRotation(rot);
}

void Slingshot::update(float delta)
{	
	if (!DragSystem::get().isDragging())
	{
		m_ChainGraphicsComponent.setTextureRect({ {0, 0}, {1, 1} });
		m_BeakPosition = m_ChainGraphicsComponent.getPosition();

		if (m_IsAiming)
		{
			m_IsAiming = false;
			
			float length = std::min(DragSystem::get().getDragDistance(), MaxDragDistance);
			float impulseRatio = std::sqrt(length / MaxDragDistance);

			m_LoadedProjectiles.front()->launch(impulseRatio, DragSystem::get().getDragDirection());
			m_LoadedProjectiles.pop();
		}

		return;
	}
	if (m_ChainGraphicsComponent.getPosition().x < GameEngine::MousePositionInGameCoords.x || m_LoadedProjectiles.size() == 0)
	{
		return;
	}	

	m_IsAiming = true;

	updateChainLength();
	updateChainRotation();
	updateBeakPosition();
}

void Slingshot::render(sf::RenderTarget& target)
{
	m_BaseGraphicsComponent.render(target);
	m_ChainGraphicsComponent.render(target);
}
