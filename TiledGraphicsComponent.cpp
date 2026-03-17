#include "TiledGraphicsComponent.h"
#include <string>
#include <SFML/Graphics/Rect.hpp>
#include "BitmapStore.h"
#include "GraphicsComponent.h"
#include <format>

TiledGraphicsComponent::TiledGraphicsComponent(BitmapStore& bitmapStore, const std::string& textureId, sf::IntRect textureRect) : GraphicsComponent(bitmapStore, textureId, textureRect)
{
	bitmapStore.getTexture(std::format("graphics/{}", textureId)).setRepeated(true);

	m_Sprite.setTexture(bitmapStore.getTexture(std::format("graphics/{}", textureId)));
	m_Sprite.setTextureRect({ {0, 0}, {7, 53*12} });
}
