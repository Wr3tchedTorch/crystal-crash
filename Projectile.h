#pragma once
#include "PhysicsObject.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "ProjectileAttributes.h"
#include "BitmapStore.h"
#include "AnimatedGraphicsAttributes.h"
#include "AnimatedGraphicsComponent.h"
#include <id.h>
#include <SFML/System/Vector2.hpp>
#include "IProjectileState.h"
#include <memory>

class Projectile : public IPhysicsObject
{
private:	
	ProjectileAttributes m_ProjectileAttributes;

	AnimatedGraphicsComponent m_GraphicsComponent;
	//SoundEngine& m_SoundEngine;
	//VelocityComponent m_VelocityComponent;

	IProjectileState* m_CurrentState;


	void createPhysicsBody();

public:
	sf::Vector2f* m_SlingshotBeakPosition;

	Projectile(BitmapStore& store, b2WorldId worldId);

	const ProjectileAttributes& getAttributes() const;

	void init(ProjectileAttributes attributes, AnimatedGraphicsAttributes animationAttributes, sf::Vector2f& slingshotBeakPosition);

	void launch(float slingShotImpulse);

	void update(float delta) override;
	void render(sf::RenderTarget& target) override;
};

