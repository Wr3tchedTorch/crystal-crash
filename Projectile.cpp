#include "Projectile.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "BitmapStore.h"
#include "ProjectileAttributes.h"

Projectile::Projectile(BitmapStore& store, ProjectileAttributes attributes) :
	m_GraphicsComponent(store, attributes.GraphicsId, { {0, 0}, {20, 20} }),
	m_ProjectileAttributes(attributes)
{
}

void Projectile::update(float delta)
{
}

void Projectile::render(sf::RenderTarget& target)
{
}
