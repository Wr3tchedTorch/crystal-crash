#pragma once
#include "PhysicsObject.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "GraphicsComponent.h"
#include "ProjectileAttributes.h"

class Projectile : public PhysicsObject
{
public:	
	ProjectileAttributes m_ProjectileAttributes;

	GraphicsComponent m_GraphicsComponent;
	//SoundEngine& m_SoundEngine;
	//VelocityComponent m_VelocityComponent;

private:
	Projectile();
	void update(float delta) override;
	void render(sf::RenderTarget& target) override;
};

