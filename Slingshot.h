#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>
#include <deque>
#include "IGameObject.h"
#include "GraphicsComponent.h"
#include "BitmapStore.h"
#include "Projectile.h"
#include "ISlingshotState.h"

class Slingshot : public IGameObject
{
	friend class StateSlingshotAiming;
	friend class StateSlingshotShooting;
	friend class StateSlingshotLoading;

private:
	GraphicsComponent m_BaseGraphicsComponent;
	GraphicsComponent m_ChainGraphicsComponent;

	std::deque<std::unique_ptr<Projectile>>  m_LoadedProjectiles;

	std::vector<std::unique_ptr<Projectile>> m_LaunchedProjectiles;

	sf::Vector2f m_BeakPosition;

	bool m_IsAiming = false;

	std::unique_ptr<ISlingshotState> m_CurrentState;

	void updateChainLength();
	void updateChainRotation();

	void updateProjectiles(float delta);
	void renderProjectiles(sf::RenderTarget& target);

	void updateBeakPosition();

public:
	Slingshot(BitmapStore& store, sf::Vector2f position);

	sf::Vector2f getIdlePosition(int order) const;
	
	void loadProjectile(std::unique_ptr<Projectile> projectile);

	void update(float delta) override;
	void render(sf::RenderTarget& target) override;

	bool isCurrentDragValid() const;
	void reset();
};

