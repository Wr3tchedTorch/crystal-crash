#include "Projectile.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "BitmapStore.h"
#include "ProjectileAttributes.h"

Projectile::Projectile(BitmapStore& store, ProjectileAttributes attributes) :
	m_GraphicsComponent(store, attributes.GraphicsAttributes.GraphicsId, attributes.GraphicsAttributes.TextureRect),
	m_ProjectileAttributes(attributes)
{
}

Projectile::Projectile(BitmapStore& store) :
	m_GraphicsComponent(store)
{
}

void Projectile::init(ProjectileAttributes attributes)
{
	m_ProjectileAttributes = attributes;

	m_GraphicsComponent.setTexture(attributes.GraphicsAttributes.GraphicsId, attributes.GraphicsAttributes.TextureRect);
}

void Projectile::update(float delta)
{
	m_GraphicsComponent.update(delta);

	m_GraphicsComponent.setPosition({ 40, 40 });
}

void Projectile::render(sf::RenderTarget& target)
{
	m_GraphicsComponent.render(target);
}
