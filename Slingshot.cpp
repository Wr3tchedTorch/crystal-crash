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
#include <memory>
#include <utility>

const std::string Slingshot::BaseGraphicsId  = "Lamp Post 1 SHORT - Silver.png";
const std::string Slingshot::ChainGraphicsId = "Chain - Bronze.png";
const sf::Vector2f Slingshot::ChainGraphicsSize = { 7.0f, 53.0f };
const float Slingshot::MaxDragDistance = 150;
const float Slingshot::SpaceBetweenIdleProjectiles = 20;

Slingshot::Slingshot(BitmapStore& store, sf::Vector2f position) :
	m_BaseGraphicsComponent(store, BaseGraphicsId),
	m_ChainGraphicsComponent(store, ChainGraphicsId, true)
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
}

sf::Vector2f Slingshot::getIdlePosition(int order) const
{
	sf::Vector2f idlePosition(m_Position);
	//idlePosition.y += m_BaseGraphicsComponent.getTextureRect().size.y / 2.0f;

	int margin = 20;

	idlePosition.x -= margin;
	idlePosition.x -= order * SpaceBetweenIdleProjectiles;

	return idlePosition;
}

void Slingshot::updateBeakPosition()
{
	float length = std::min(DragSystem::get().getDragDistance(), MaxDragDistance);
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
			
			float length = std::min(DragSystem::get().getDragDistance(), MaxDragDistance);
			float impulseRatio = std::sqrt(length / MaxDragDistance);

			m_LoadedProjectiles.front()->launch(impulseRatio, DragSystem::get().getDragDirection());

			m_LaunchedProjectiles.push_back(std::move(m_LoadedProjectiles.front()));
			m_LoadedProjectiles.pop_front();

			if (!m_LoadedProjectiles.empty())
			{
				m_LoadedProjectiles.front()->load();
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
