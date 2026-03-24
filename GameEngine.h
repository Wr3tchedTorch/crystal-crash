#pragma once

#include <id.h>

#include <vector>
#include <memory>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "MouseDragHandler.h"
#include "World.h"
#include "LevelManager.h"
#include "EventHandler.h"
#include "BitmapStore.h"
#include "PhysicsEngine.h"
#include "ProjectilesFactory.h"
#include "DataHandlerManager.h"

class GameEngine
{
private:
	sf::RenderWindow m_Window;
	EventHandler	 m_EventHandler;
	MouseDragHandler m_MouseDragHandler;

	BitmapStore	  m_BitmapStore;
	PhysicsEngine m_PhysicsEngine;

	DataHandlerManager m_DataManager;

	std::shared_ptr<ProjectilesFactory> m_ProjectileFactory;
	std::unique_ptr<LevelManager> m_LevelManager;
	std::unique_ptr<World> m_CurrentWorld;

	std::vector<sf::RectangleShape> m_DebugBoxes;
	std::vector<b2BodyId> m_DebugBoxesIds;

	static bool Instantiated;

public:
	static sf::Time GameTimeTotal;
	static sf::Vector2f MousePositionInGameCoords;

	GameEngine();
	~GameEngine();
	
	void run();	

	void spawnBox(sf::FloatRect transform);
	void spawnBoxes();
};

