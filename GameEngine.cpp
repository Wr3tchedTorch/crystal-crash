#include "GameEngine.h"
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <cassert>
#include "GameScreen.h"
#include "ProjectileAttributes.h"
#include "AnimatedGraphicsAttributes.h"
#include <box2d.h>
#include <types.h>
#include <collision.h>
#include "Converter.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <math_functions.h>
#include "DragSystem.h"

bool GameEngine::Instantiated = false;
sf::Time GameEngine::GameTimeTotal = sf::Time();

GameEngine::GameEngine() : 
	m_EventHandler(m_Window, m_MouseDragHandler),
	m_Projectile(m_BitmapStore, m_PhysicsEngine.getWorldId()),
	m_Slingshot(m_BitmapStore, {100, 500})
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
	anAttr.TextureRect = { {0, 0}, {23, 27} };

	ProjectileAttributes attr;
	attr.GraphicsAttributes.GraphicsId  = "GEM 2 - LIGHT GREEN.png";

	m_Projectile.init(attr, anAttr);

	spawnGround();

	DragSystem::initialize(m_MouseDragHandler);
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

		float delta = deltaTime.asSeconds();

		m_PhysicsEngine.update(delta);
		m_Projectile.update(delta);
		m_Slingshot.update(delta);

		m_Window.clear();

		m_Projectile.render(m_Window);
		m_Slingshot.render(m_Window);
		m_Window.draw(m_DebugGround);		

		//if (m_CurrentScreen)
		//{
		//	m_CurrentScreen->render(m_Window);
		//}

		m_Window.display();
	}
}

void GameEngine::spawnGround()
{
	sf::FloatRect bounds({
		{1920.0f/2.0f, 1000.0f},
		{1920.0f, 100.0f}
	});
	m_DebugGround.setOrigin({ bounds.size.x / 2.0f, bounds.size.y / 2.0f });
	m_DebugGround.setPosition(bounds.position);
	m_DebugGround.setSize(bounds.size);
	m_DebugGround.setFillColor(sf::Color::White);

	bounds.size /= 2.0f;

	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_staticBody;
	bodyDef.position = converter::pixelsToMeters(bounds.position);

	auto bodyId = b2CreateBody(m_PhysicsEngine.getWorldId(), &bodyDef);

	b2Vec2 sizeInMeters = converter::pixelsToMeters(bounds.size);
	b2Polygon  polygon = b2MakeBox(sizeInMeters.x, sizeInMeters.y);

	b2ShapeDef shapeDef = b2DefaultShapeDef();	
}
