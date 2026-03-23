#include "World.h"
#include "DataHandler.h"
#include <format>
#include <memory>
#include "BitmapStore.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "IGameObject.h"
#include "WorldData.h"
#include "Tilemap.h"
#include "TilemapAttributes.h"

World::World(int levelToLoad, BitmapStore& store, DataHandler<WorldData>& dataHandler)
{
	m_WorldData = dataHandler.getById(levelToLoad);

	DataHandler<TilemapAttributes> tilemapDataHandler(std::format("maps/{}/map.json", m_WorldData->TilemapId));
	m_WorldData->setTilemapAttributes(tilemapDataHandler.getById(0));

	m_Tilemap = std::make_unique<Tilemap>(store.getTexture(std::format("maps/{}/spritesheet.png", m_WorldData->TilemapId)), m_WorldData->getTilemapAttributes());
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
	target.draw(*m_Tilemap.get());
}
