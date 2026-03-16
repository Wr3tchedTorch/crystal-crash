#pragma once
#include "PhysicsObject.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "ProjectileAttributes.h"
#include "BitmapStore.h"
#include "AnimatedGraphicsAttributes.h"
#include "GraphicsComponent.h"
#include "AnimatedGraphicsComponent.h"

class Projectile : public PhysicsObject
{
private:	
	ProjectileAttributes m_ProjectileAttributes;

	AnimatedGraphicsComponent m_GraphicsComponent;
	//SoundEngine& m_SoundEngine;
	//VelocityComponent m_VelocityComponent;

public:
	Projectile(BitmapStore& store);

	void init(ProjectileAttributes attributes, AnimatedGraphicsAttributes animationAttributes);

	void update(float delta) override;
	void render(sf::RenderTarget& target) override;
};

