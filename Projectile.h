#pragma once
#include "PhysicsObject.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "GraphicsComponent.h"
#include "ProjectileAttributes.h"
#include "BitmapStore.h"

class Projectile : public PhysicsObject
{
public:	
	ProjectileAttributes m_ProjectileAttributes;

	GraphicsComponent m_GraphicsComponent;
	//SoundEngine& m_SoundEngine;
	//VelocityComponent m_VelocityComponent;

private:
	Projectile(BitmapStore& store, ProjectileAttributes attributes);
	Projectile(BitmapStore& store);

	void init(ProjectileAttributes attributes);
	void update(float delta) override;
	void render(sf::RenderTarget& target) override;
};

