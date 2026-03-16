#include "Projectile.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "BitmapStore.h"
#include "ProjectileAttributes.h"
#include "AnimatedGraphicsAttributes.h"

Projectile::Projectile(BitmapStore& store) :
	m_GraphicsComponent(store)
{
}

void Projectile::init(ProjectileAttributes attributes, AnimatedGraphicsAttributes animationAttributes)
{
	m_ProjectileAttributes = attributes;

	m_GraphicsComponent.init(animationAttributes);
	m_GraphicsComponent.setTexture(attributes.GraphicsAttributes.GraphicsId, attributes.GraphicsAttributes.TextureRect);

	m_GraphicsComponent.setPosition({ 40, 40 });
}

void Projectile::update(float delta)
{
	m_GraphicsComponent.update(delta);
}

void Projectile::render(sf::RenderTarget& target)
{
	m_GraphicsComponent.render(target);
}
