#pragma once
#include <SFML/System/Vector2.hpp>

class IDragState
{
public:
	virtual sf::Vector2f getDragDirection() = 0;
	virtual sf::Vector2f getDragStartPosition() = 0;
	virtual sf::Vector2f getDragEndPosition() = 0;
	virtual float getDragDistance() = 0;
	virtual bool  isDragging() = 0;
};