#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "EventHandler.h"
#include "IScreen.h"
#include "BitmapStore.h"
#include "Projectile.h"
#include <SFML/System/Time.hpp>
#include "PhysicsEngine.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "MouseDragHandler.h"
#include "Slingshot.h"
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <id.h>
#include <SFML/Graphics/Rect.hpp>

class GameEngine
{
private:
	sf::RenderWindow m_Window;
	EventHandler	 m_EventHandler;
	MouseDragHandler m_MouseDragHandler;

	BitmapStore	  m_BitmapStore;
	PhysicsEngine m_PhysicsEngine;

	IScreen* m_CurrentScreen;

	Slingshot  m_Slingshot;

	static bool Instantiated;

	sf::RectangleShape m_DebugGround;

	std::vector<sf::RectangleShape> m_DebugBoxes;
	std::vector<b2BodyId> m_DebugBoxesIds;

public:
	static sf::Time GameTimeTotal;
	static sf::Vector2f MousePositionInGameCoords;

	GameEngine();
	~GameEngine();
	
	void run();	

	void spawnGround();
	void spawnBox(sf::FloatRect transform);
	void spawnBoxes();
};

