#include "GameEngine.h"
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <cassert>
#include "GameScreen.h"
#include "ProjectileAttributes.h"

bool GameEngine::Instantiated = false;

GameEngine::GameEngine() : 
	m_EventHandler(m_Window),
	m_Projectile(m_BitmapStore)
{
	assert(!Instantiated);
	Instantiated = true;

	m_Window.create(sf::VideoMode::getDesktopMode(), "Crystal Crash by Eric");
	m_Window.setFramerateLimit(60);

	m_CurrentScreen = new GameScreen;

	ProjectileAttributes attr;
	attr.GraphicsAttributes.GraphicsId  = "GEM 2 - LIGHT GREEN.png";
	attr.GraphicsAttributes.TextureRect = { {0, 0}, {23, 27} };

	m_Projectile.init(attr);
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
		m_Projectile.update(deltaTime.asSeconds());

		m_Window.clear();

		m_Projectile.render(m_Window);

		//if (m_CurrentScreen)
		//{
		//	m_CurrentScreen->render(m_Window);
		//}

		m_Window.display();
	}
}
