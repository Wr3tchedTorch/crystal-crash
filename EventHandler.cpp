#include "EventHandler.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <cassert>
#include <SFML/Window/Keyboard.hpp>
#include "MouseDragHandler.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

bool EventHandler::Instantiated = false;

EventHandler::EventHandler(sf::RenderWindow& window, MouseDragHandler& mouseDragHandler) : m_Window(window), m_MouseDragHandler(mouseDragHandler)
{
	assert(!Instantiated);
	Instantiated = true;
}

void EventHandler::updateCurrentView(sf::View& currentView)
{
	m_CurrentView = &currentView;
}

void EventHandler::operator()(const sf::Event::KeyPressed& key)
{
	if (key.scancode == sf::Keyboard::Scancode::Escape)
	{
		m_Window.close();
	}
}

void EventHandler::operator()(const sf::Event::MouseButtonPressed& event)
{
	if (event.button == sf::Mouse::Button::Left)
	{
		m_MouseDragHandler.startDrag();
	}
}

void EventHandler::operator()(const sf::Event::MouseButtonReleased& event)
{
	if (event.button == sf::Mouse::Button::Left)
	{
		m_MouseDragHandler.endDrag();
	}
}

void EventHandler::operator()(const sf::Event::MouseMoved& event)
{
	sf::Vector2f mousePosition = m_CurrentView ? m_Window.mapPixelToCoords(event.position, *m_CurrentView) :
												 m_Window.mapPixelToCoords(event.position);

	m_MouseDragHandler.update(mousePosition);
}

void EventHandler::operator()(const sf::Event::Closed& event)
{
	m_Window.close();
}
