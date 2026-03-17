#pragma once
#include <SFML/System/Vector2.hpp>
#include "IDragState.h"

class MouseDragHandler : public IDragState
{
private:
	sf::Vector2f m_DragStartPosition;
	sf::Vector2f m_DragEndPosition;
	sf::Vector2f m_CurrentMousePosition;

	float m_DragDistance = 0;
	sf::Vector2f m_DragDirection;

	bool m_IsDragging   = false;
	
	static bool m_Instantiated;

public:
	MouseDragHandler();
	void startDrag();
	void endDrag();

	void update(sf::Vector2f mousePosition);

	sf::Vector2f getDragDirection() override;
	sf::Vector2f getDragStartPosition() override;
	sf::Vector2f getDragEndPosition() override;
	float getDragDistance() override;

};

