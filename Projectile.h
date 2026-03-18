#pragma once
#include "PhysicsObject.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "ProjectileAttributes.h"
#include "BitmapStore.h"
#include "AnimatedGraphicsComponent.h"
#include <id.h>
#include <SFML/System/Vector2.hpp>
#include "IProjectileState.h"
#include <memory>
#include <types.h>

class Projectile : public IPhysicsObject
{
private:	
	std::shared_ptr<ProjectileAttributes> m_ProjectileAttributes;

	AnimatedGraphicsComponent m_GraphicsComponent;
	//SoundEngine& m_SoundEngine;
	//VelocityComponent m_VelocityComponent;

	IProjectileState* m_CurrentState;
	BitmapStore&      m_BitmapStore;

	sf::Vector2f m_SlingshotBeakPosition;

public:
	Projectile(BitmapStore& store, b2WorldId worldId, b2BodyId body, std::shared_ptr<ProjectileAttributes> attributes);

	const ProjectileAttributes* getAttributes() const;

	void launch(float slingShotImpulseRatio, sf::Vector2f normalizedDirection);

	sf::Vector2f getSlingshotBeakPosition() const;
	void setSlingShotBeakPosition(sf::Vector2f toPosition);

	void update(float delta) override;
	void render(sf::RenderTarget& target) override;

	std::unique_ptr<Projectile> clone();
};

