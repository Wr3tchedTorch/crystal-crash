#pragma once
#include "IGameObject.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "GraphicsComponent.h"
#include "BitmapStore.h"
#include <SFML/System/Vector2.hpp>
#include <string>
#include "Projectile.h"
#include <memory>
#include <vector>
#include <deque>

class Slingshot : public IGameObject
{
private:
	GraphicsComponent m_BaseGraphicsComponent;
	GraphicsComponent m_ChainGraphicsComponent;

	std::deque<std::unique_ptr<Projectile>> m_LoadedProjectiles;

	std::vector<std::unique_ptr<Projectile>> m_LaunchedProjectiles;

	sf::Vector2f m_BeakPosition;

	bool m_IsAiming = false;

	void updateChainLength();
	void updateChainRotation();

	void updateProjectiles(float delta);
	void renderProjectiles(sf::RenderTarget& target);

public:
	static const std::string  BaseGraphicsId;
	static const std::string  ChainGraphicsId;
	static const sf::Vector2f ChainGraphicsSize;
	static const float MaxDragDistance;
	static const float SpaceBetweenIdleProjectiles;

	Slingshot(BitmapStore& store, sf::Vector2f position);

	sf::Vector2f getIdlePosition(int order) const;
	void updateBeakPosition();
	
	void loadProjectile(std::unique_ptr<Projectile> projectile);

	void update(float delta) override;
	void render(sf::RenderTarget& target) override;
};

