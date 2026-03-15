#include "EventHandler.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <cassert>
#include <SFML/Window/Keyboard.hpp>

bool EventHandler::Instantiated = false;

EventHandler::EventHandler(sf::RenderWindow& window) : m_Window(window)
{
	assert(!Instantiated);
	Instantiated = true;
}

void EventHandler::operator()(const sf::Event::KeyPressed& key)
{
	if (key.scancode == sf::Keyboard::Scancode::Escape)
	{
		m_Window.close();
	}
}

void EventHandler::operator()(const sf::Event::Closed& event)
{
	m_Window.close();
}
