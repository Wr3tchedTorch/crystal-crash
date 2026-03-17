#pragma once
#include "GraphicsComponent.h"
#include <SFML/Graphics/Rect.hpp>
#include <string>
#include "BitmapStore.h"

class TiledGraphicsComponent : public GraphicsComponent
{
private:
	sf::IntRect m_Size;

public:
	TiledGraphicsComponent(BitmapStore& bitmapStore, const std::string& textureId, sf::IntRect textureRect = { {0, 0}, {0, 0} });

};

