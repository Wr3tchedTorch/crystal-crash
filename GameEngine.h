#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "EventHandler.h"

class GameEngine
{
private:
	sf::RenderWindow m_Window;
	EventHandler m_EventHandler;

	static bool Instantiated;

public:
	GameEngine();
	~GameEngine();
	
	void run();	
};

