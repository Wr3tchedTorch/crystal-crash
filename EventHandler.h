#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "MouseDragHandler.h"
#include <SFML/Graphics/View.hpp>

class EventHandler
{
private:
	sf::RenderWindow& m_Window;
	MouseDragHandler& m_MouseDragHandler;

	sf::View* m_CurrentView = nullptr;

	static bool Instantiated;

public:	
	EventHandler(sf::RenderWindow& window, MouseDragHandler& mouseDragHandler);

	void updateCurrentView(sf::View& currentView);

	void operator()(const sf::Event::KeyPressed& key);

	void operator()(const sf::Event::MouseButtonPressed& event);
	void operator()(const sf::Event::MouseButtonReleased& event);
	void operator()(const sf::Event::MouseMoved& event);

	void operator()(const sf::Event::Closed& event);

	template <typename T>
	void operator()(const T&) const { };
};

