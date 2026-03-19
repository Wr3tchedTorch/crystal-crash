#include "Slingshot.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdlib>
#include <SFML/System/Angle.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <memory>
#include <utility>
#include "BitmapStore.h"
#include "DragSystem.h"
#include "GameEngine.h"
#include "Projectile.h"
#include "SlingshotConstants.h"

Slingshot::Slingshot(BitmapStore& store, sf::Vector2f position) :
	m_BaseGraphicsComponent(store, SlingshotConstants::BaseGraphicsId),
	m_ChainGraphicsComponent(store, SlingshotConstants::ChainGraphicsId, true)
{
	m_Position = position;

	m_BaseGraphicsComponent.resetTextureRect();
	m_BaseGraphicsComponent.setPosition(m_Position);
	m_BaseGraphicsComponent.setOriginToCenter();

	sf::Vector2f chainPosition(m_Position);
	chainPosition.y -= m_BaseGraphicsComponent.getTextureRect().size.y/2.0f;

	m_ChainGraphicsComponent.resetTextureRect();
	m_ChainGraphicsComponent.setPosition(chainPosition);
	m_ChainGraphicsComponent.setOriginToTopCenter();

	m_BeakPosition = m_ChainGraphicsComponent.getPosition();
	m_BeakPosition.x += 2;
}

sf::Vector2f Slingshot::getIdlePosition(int order) const
{
	sf::Vector2f idlePosition(m_Position);	

	idlePosition.x -= SlingshotConstants::MarginBetweenProjectilesAndSlingshot;
	idlePosition.x -= order * SlingshotConstants::SpaceBetweenIdleProjectiles;

	return idlePosition;
}

void Slingshot::updateBeakPosition()
{
	float length = std::min(DragSystem::get().getDragDistance(), SlingshotConstants::MaxDragDistance);
	length = std::abs(length);

	m_BeakPosition = m_ChainGraphicsComponent.getPosition();
	m_BeakPosition += DragSystem::get().getDragDirection() * length;

	if (!m_LoadedProjectiles.empty())
	{
		m_LoadedProjectiles.front()->setSlingShotBeakPosition(m_BeakPosition);
	}
}

void Slingshot::loadProjectile(std::unique_ptr<Projectile> projectile)
{
	projectile->setSlingShotBeakPosition(m_BeakPosition);
	m_LoadedProjectiles.push_back(std::move(projectile));

	if (!m_LoadedProjectiles.front()->isLoaded())
	{
		m_LoadedProjectiles.front()->load();		
	}
}

void Slingshot::updateChainLength()
{
	float length = std::min(DragSystem::get().getDragDistance(), SlingshotConstants::MaxDragDistance);
	length = std::abs(length);

	sf::IntRect textureRect;
	textureRect.position = { 0, 0 };
	textureRect.size = {
		static_cast<int>(m_ChainGraphicsComponent.getTextureSize().x),
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

void Slingshot::updateProjectiles(float delta)
{
	for (auto& projectile : m_LaunchedProjectiles)
	{
		projectile->update(delta);
	}
	for (auto& projectile : m_LoadedProjectiles)
	{
		projectile->update(delta);
	}
}

void Slingshot::renderProjectiles(sf::RenderTarget& target)
{
	for (auto& projectile : m_LaunchedProjectiles)
	{
		projectile->render(target);
	}
	for (auto& projectile : m_LoadedProjectiles)
	{
		projectile->render(target);
	}
}

void Slingshot::update(float delta)
{	
	updateProjectiles(delta);

	if (!DragSystem::get().isDragging())
	{
		m_ChainGraphicsComponent.setTextureRect({ {0, 0}, {1, 1} });
		m_BeakPosition = m_ChainGraphicsComponent.getPosition();

		if (m_IsAiming)
		{
			m_IsAiming = false;
			
			float length = std::min(DragSystem::get().getDragDistance(), SlingshotConstants::MaxDragDistance);
			float impulseRatio = std::sqrt(length / SlingshotConstants::MaxDragDistance);

			m_LoadedProjectiles.front()->launch(impulseRatio, DragSystem::get().getDragDirection());

			m_LaunchedProjectiles.push_back(std::move(m_LoadedProjectiles.front()));
			m_LoadedProjectiles.pop_front();

			if (!m_LoadedProjectiles.empty())
			{
				m_LoadedProjectiles.front()->load();
				m_LoadedProjectiles.front()->setRotation(sf::degrees(0));
			}
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

	renderProjectiles(target);

	m_ChainGraphicsComponent.render(target);
}
