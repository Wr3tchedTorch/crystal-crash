#include "World.h"
#include "DataHandler.h"
#include "TilemapAttributes.h"
#include <format>
#include <memory>
#include "Tilemap.h"
#include "BitmapStore.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "IGameObject.h"

World::World(int levelToLoad, BitmapStore& store)
{
	DataHandler<TilemapAttributes> tilemapDatahandler(std::format("maps/{}/map.json", levelToLoad));

	std::shared_ptr<TilemapAttributes> tilemapAttributes = tilemapDatahandler.getById(0);
	m_Tilemap = std::make_unique<Tilemap>(store, tilemapAttributes);
}

void World::update(float delta)
{
	for (auto& [key, entity] : m_ActiveEntities)
	{
		entity->update(delta);
	}
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& [key, entity] : m_ActiveEntities)
	{
		entity->render(target);
	}
}
