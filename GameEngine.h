#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "EventHandler.h"
#include "Screen.h"

class GameEngine
{
private:
	sf::RenderWindow m_Window;
	EventHandler m_EventHandler;

	Screen* m_CurrentScreen;

	static bool Instantiated;

public:
	GameEngine();
	~GameEngine();
	
	void run();	
};

