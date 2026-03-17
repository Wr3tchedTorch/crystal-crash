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

class GameEngine
{
private:
	sf::RenderWindow m_Window;
	EventHandler	 m_EventHandler;
	MouseDragHandler m_MouseDragHandler;

	BitmapStore	  m_BitmapStore;
	PhysicsEngine m_PhysicsEngine;

	IScreen* m_CurrentScreen;

	Projectile m_Projectile;

	static bool Instantiated;

	sf::RectangleShape m_DebugGround;

public:
	static sf::Time GameTimeTotal;

	GameEngine();
	~GameEngine();
	
	void run();	

	void spawnGround();
};

