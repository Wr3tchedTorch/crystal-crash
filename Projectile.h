#pragma once
#include "PhysicsObject.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "ProjectileAttributes.h"
#include "BitmapStore.h"
#include "AnimatedGraphicsComponent.h"
#include <id.h>
#include <SFML/System/Vector2.hpp>
#include "IProjectileState.h"
#include "GraphicsAttributes.h"
#include <memory>

class Projectile : public IPhysicsObject
{
private:	
	std::shared_ptr<ProjectileAttributes> m_ProjectileAttributes;

	AnimatedGraphicsComponent m_GraphicsComponent;
	//SoundEngine& m_SoundEngine;
	//VelocityComponent m_VelocityComponent;

	IProjectileState* m_CurrentState;

public:
	sf::Vector2f* m_SlingshotBeakPosition;

	Projectile(BitmapStore& store, b2WorldId worldId);

	const std::shared_ptr<ProjectileAttributes> getAttributes() const;

	void init(std::shared_ptr<ProjectileAttributes> attributes, std::shared_ptr<GraphicsAttributes> animationAttributes, sf::Vector2f& slingshotBeakPosition, b2BodyId body);

	void launch(float slingShotImpulseRatio, sf::Vector2f normalizedDirection);

	void update(float delta) override;
	void render(sf::RenderTarget& target) override;
};

