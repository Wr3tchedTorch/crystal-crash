#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "EventHandler.h"
#include "BitmapStore.h"
#include <SFML/System/Time.hpp>
#include "PhysicsEngine.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "MouseDragHandler.h"
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <id.h>
#include <SFML/Graphics/Rect.hpp>
#include "WorldData.h"
#include "DataHandler.h"
#include <memory>
#include "World.h"
#include "ProjectileAttributes.h"

class GameEngine
{
private:
	sf::RenderWindow m_Window;
	EventHandler	 m_EventHandler;
	MouseDragHandler m_MouseDragHandler;

	BitmapStore	  m_BitmapStore;
	PhysicsEngine m_PhysicsEngine;

	std::unique_ptr<DataHandler<WorldData>> m_WorldDataHandler;
	std::unique_ptr<DataHandler<ProjectileAttributes>> m_ProjectileDataHandler;


	std::unique_ptr<World> m_World;

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

