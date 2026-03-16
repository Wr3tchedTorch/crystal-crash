#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "EventHandler.h"
#include "Screen.h"
#include "BitmapStore.h"
#include "Projectile.h"
#include <SFML/System/Time.hpp>

class GameEngine
{
private:
	sf::RenderWindow m_Window;
	EventHandler m_EventHandler;
	BitmapStore	 m_BitmapStore;

	Screen* m_CurrentScreen;

	Projectile m_Projectile;

	static bool Instantiated;

public:
	static sf::Time GameTimeTotal;

	GameEngine();
	~GameEngine();
	
	void run();	
};

