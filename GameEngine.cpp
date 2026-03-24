#include "GameEngine.h"

#include <box2d.h>
#include <types.h>
#include <collision.h>
#include <math_functions.h>

#include <cassert>
#include <random>
#include <memory>

#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Converter.h"
#include "DragSystem.h"
#include "World.h"
#include "ProjectilesFactory.h"
#include "LevelManager.h"

bool GameEngine::Instantiated = false;
sf::Time GameEngine::GameTimeTotal = sf::Time();
sf::Vector2f GameEngine::MousePositionInGameCoords = sf::Vector2f();

GameEngine::GameEngine() : 	
	m_EventHandler(m_Window, m_MouseDragHandler)
{
	assert(!Instantiated);
	Instantiated = true;

	DragSystem::initialize(m_MouseDragHandler);

	m_Window.create(sf::VideoMode::getDesktopMode(), "Crystal Crash by Eric");
	m_Window.setFramerateLimit(60);	

	spawnBoxes();

	m_ProjectileFactory = std::make_shared<ProjectilesFactory>(m_BitmapStore, m_PhysicsEngine.getWorldId());
	m_LevelManager		= std::make_unique<LevelManager>(m_BitmapStore, m_ProjectileFactory, m_DataManager);
	m_CurrentWorld		= m_LevelManager->loadLevel(1);
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

		MousePositionInGameCoords = m_Window.mapPixelToCoords(sf::Mouse::getPosition());

		m_PhysicsEngine.update(delta);
		if (m_CurrentWorld)
		{
			m_CurrentWorld->update(delta);
		}

		for (int i = 0; i < m_DebugBoxes.size(); i++)
		{			
			b2Vec2 position = b2Body_GetPosition(m_DebugBoxesIds.at(i));
			b2Rot  rotation = b2Body_GetRotation(m_DebugBoxesIds.at(i));

			m_DebugBoxes.at(i).setPosition(converter::metersToPixels(position));
			m_DebugBoxes.at(i).setRotation(converter::rotToAngle(rotation));
		}

		m_Window.clear(sf::Color(135, 206, 250));

		if (m_CurrentWorld)
		{
			m_Window.draw(*m_CurrentWorld.get());
		}
		for (auto& box : m_DebugBoxes)
		{
			m_Window.draw(box);
		}

		m_Window.display();
	}
}

void GameEngine::spawnBox(sf::FloatRect transform)
{	
	m_DebugBoxes.push_back(sf::RectangleShape());
	m_DebugBoxes.back().setOrigin({ transform.size.x / 2.0f, transform.size.y / 2.0f });
	m_DebugBoxes.back().setPosition(transform.position);
	m_DebugBoxes.back().setSize(transform.size);
	m_DebugBoxes.back().setFillColor(sf::Color(199, 157, 122));

	transform.size /= 2.0f;

	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = converter::pixelsToMeters(transform.position);

	auto bodyId = b2CreateBody(m_PhysicsEngine.getWorldId(), &bodyDef);

	b2Vec2 sizeInMeters = converter::pixelsToMeters(transform.size);
	b2Polygon  polygon = b2MakeBox(sizeInMeters.x, sizeInMeters.y);

	b2ShapeDef shapeDef = b2DefaultShapeDef();
	shapeDef.density = 1.0f;
	shapeDef.material.friction = .3f;

	b2CreatePolygonShape(bodyId, &shapeDef, &polygon);

	m_DebugBoxesIds.push_back(bodyId);
}

void GameEngine::spawnBoxes()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(30, 40);
	std::uniform_int_distribution<> heightDist(-3, 3);
	std::uniform_real_distribution<float> distSize(0.5f, 2.0f);

	int boxCount = 5;
	for (int i = 0; i < 35; i++)
	{
		int result = dist(gen);

		sf::FloatRect transform;
		transform.position = { static_cast<float>(converter::metersToPixels(dist(gen))), static_cast<float>(converter::metersToPixels(heightDist(gen))) };
		transform.size = { converter::metersToPixels(distSize(gen)), converter::metersToPixels(distSize(gen)) };

		spawnBox(transform);
	}
}
