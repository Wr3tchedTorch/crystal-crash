#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class EventHandler
{
private:
	sf::RenderWindow& m_Window;

	static bool Instantiated;

public:	
	EventHandler(sf::RenderWindow& window);

	void operator()(const sf::Event::KeyPressed& key);

	void operator()(const sf::Event::Closed& event);

	template <typename T>
	void operator()(const T&) const { };
};

