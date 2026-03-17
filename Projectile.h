#pragma once
#include "PhysicsObject.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "ProjectileAttributes.h"
#include "BitmapStore.h"
#include "AnimatedGraphicsAttributes.h"
#include "AnimatedGraphicsComponent.h"
#include <id.h>
#include <SFML/System/Vector2.hpp>
#include "IState.h"

class Projectile : public IPhysicsObject
{
private:	
	ProjectileAttributes m_ProjectileAttributes;

	AnimatedGraphicsComponent m_GraphicsComponent;
	//SoundEngine& m_SoundEngine;
	//VelocityComponent m_VelocityComponent;

	IState* m_CurrentState;

	void createPhysicsBody();

public:
	Projectile(BitmapStore& store, b2WorldId worldId);

	void init(ProjectileAttributes attributes, AnimatedGraphicsAttributes animationAttributes, sf::Vector2f& slingshotBeakPosition);

	void update(float delta) override;
	void render(sf::RenderTarget& target) override;
};

