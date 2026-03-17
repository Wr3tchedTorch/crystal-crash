#pragma once
#include "IGameObject.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "GraphicsComponent.h"
#include "BitmapStore.h"
#include <SFML/System/Vector2.hpp>
#include <string>
#include <queue>
#include "Projectile.h"

class Slingshot : public IGameObject
{
private:
	GraphicsComponent m_BaseGraphicsComponent;
	GraphicsComponent m_ChainGraphicsComponent;

	std::queue<Projectile*> m_LoadedProjectiles;

	sf::Vector2f m_BeakPosition;

	void updateChainLength();
	void updateChainRotation();

public:
	static const std::string  BaseGraphicsId;
	static const std::string  ChainGraphicsId;
	static const sf::Vector2f ChainGraphicsSize;
	static const float MaxDragDistance;

	Slingshot(BitmapStore& store, sf::Vector2f position);

	sf::Vector2f& getBeakPosition();
	void updateBeakPosition();
	
	void loadProjectile(Projectile* projectile);

	void update(float delta) override;
	void render(sf::RenderTarget& target) override;
};

