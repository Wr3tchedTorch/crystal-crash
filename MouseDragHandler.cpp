#include "MouseDragHandler.h"
#include <SFML/System/Vector2.hpp>
#include <cassert>

bool MouseDragHandler::m_Instantiated = false;

MouseDragHandler::MouseDragHandler()
{
	assert(!m_Instantiated);
	m_Instantiated = true;
}

void MouseDragHandler::startDrag()
{
	m_DragStartPosition = m_CurrentMousePosition;
	m_DragEndPosition   = m_CurrentMousePosition;
	m_DragDirection = { 0, 0 };
	m_DragDistance  = 0;

	m_IsDragging = true;
}

void MouseDragHandler::endDrag()
{
	m_IsDragging = false;
}

void MouseDragHandler::update(sf::Vector2f mousePosition)
{
	m_CurrentMousePosition = mousePosition;
	if (m_IsDragging)
	{
		m_DragEndPosition = m_CurrentMousePosition;
		m_DragDirection   = m_DragEndPosition - m_DragStartPosition;
		m_DragDistance    = m_DragDirection.length();
		m_DragDirection   = m_DragDirection.normalized();
	}
}

sf::Vector2f MouseDragHandler::getDragDirection()
{
	return m_DragDirection;
}

sf::Vector2f MouseDragHandler::getDragStartPosition()
{
	return m_DragStartPosition;
}

sf::Vector2f MouseDragHandler::getDragEndPosition()
{
	return m_DragEndPosition;
}

float MouseDragHandler::getDragDistance()
{
	return m_DragDistance;
}
