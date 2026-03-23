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
#include "Slingshot.h"
#include <utility>

World::World(int levelToLoad, BitmapStore& store, DataHandler<WorldData>& dataHandler)
{
	m_WorldData = dataHandler.getById(levelToLoad);

	DataHandler<TilemapAttributes> tilemapDataHandler(std::format("./maps/{}/map.json", m_WorldData->TilemapId));

	auto map = tilemapDataHandler.getById(m_WorldData->TilemapId);
	m_WorldData->setTilemapAttributes(map);

	m_Tilemap = std::make_unique<Tilemap>(store.getTexture(std::format("./maps/{}/spritesheet.png", m_WorldData->TilemapId)), m_WorldData->getTilemapAttributes());

	auto slingshot = std::make_unique<Slingshot>(store, m_WorldData->SlingshotData.Position);

	m_Entities.push_back(std::move(slingshot));
}

void World::update(float delta)
{
	for (auto& entity : m_Entities)
	{
		entity->update(delta);
	}
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& entity : m_Entities)
	{
		entity->render(target);
	}
	target.draw(*m_Tilemap.get());
}
