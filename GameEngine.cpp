#include "GameEngine.h"
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <cassert>

bool GameEngine::Instantiated = false;

GameEngine::GameEngine() : m_EventHandler(m_Window)
{
	assert(!Instantiated);
	Instantiated = true;

	m_Window.create(sf::VideoMode::getDesktopMode(), "Crystal Crash by Eric");
	m_Window.setFramerateLimit(60);
}

GameEngine::~GameEngine()
{
	Instantiated = false;
}

void GameEngine::run()
{
	sf::Clock clock;
	while (m_Window.isOpen())
	{
		m_Window.handleEvents(m_EventHandler);

		sf::Time deltaTime = clock.restart();

		m_Window.clear();

		m_Window.display();
	}
}
