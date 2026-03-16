#include "GameEngine.h"
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <cassert>
#include "GameScreen.h"
#include "ProjectileAttributes.h"
#include "AnimatedGraphicsAttributes.h"

bool GameEngine::Instantiated = false;
sf::Time GameEngine::GameTimeTotal = sf::Time();

GameEngine::GameEngine() : 
	m_EventHandler(m_Window),
	m_Projectile(m_BitmapStore)
{
	assert(!Instantiated);
	Instantiated = true;

	m_Window.create(sf::VideoMode::getDesktopMode(), "Crystal Crash by Eric");
	m_Window.setFramerateLimit(60);

	m_CurrentScreen = new GameScreen;

	AnimatedGraphicsAttributes anAttr;
	anAttr.AnimationCount = 1;
	anAttr.DelayBetweenFrames = .100f;
	anAttr.DelayBeforeAnimationStart = 1;
	anAttr.FrameCount = 10;
	anAttr.Loop = true;
	anAttr.SpriteSize = { 23, 27 };

	ProjectileAttributes attr;
	attr.GraphicsAttributes.GraphicsId  = "GEM 2 - LIGHT GREEN.png";

	m_Projectile.init(attr, anAttr);
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
		GameTimeTotal += deltaTime;

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
