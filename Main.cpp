#include "DataHandler.h"
#include "DataHandlingConstants.h"
#include "GraphicsAttributes.h"
#include <memory>
#include <iostream>
#include "TilemapAttributes.h"
#include "Tilemap.h"
#include "BitmapStore.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>

int main()
{
	//GameEngine engine;

	//engine.run();

	BitmapStore store;
	
	DataHandler<GraphicsAttributes> graphicsDatahandler(DataHandlingConstants::FilepathGraphicsAttributes);

	auto graph = graphicsDatahandler.getById(2);
	auto graph2 = graphicsDatahandler.getById(1);

	std::cout << graph->ImageId;

	DataHandler<TilemapAttributes> tilemapDatahandler("./maps/01/map.json");
	
	Tilemap tilemap(store.getTexture("./maps/01/spritesheet.png"), tilemapDatahandler.getById(0));

	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Testing Tilemap Rendering");

	while (window.isOpen())
	{
		while (auto event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		window.clear();

		window.draw(tilemap);

		window.display();
	}

	return 0;
}