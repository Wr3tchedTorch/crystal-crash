#pragma once
#include "Tilemap.h"
#include <memory>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "BitmapStore.h"
#include <string>
#include <unordered_map>
#include "WorldData.h"
#include "DataHandler.h"

class IGameObject;

using GameObjectsMap = std::unordered_map<std::string, std::unique_ptr<IGameObject>>;

class World : public sf::Drawable
{
private:
	GameObjectsMap m_ActiveEntities;
	GameObjectsMap m_InactiveEntities;

	std::unique_ptr<Tilemap> m_Tilemap;

	std::shared_ptr<WorldData> m_WorldData;

public:
	World(int levelToLoad, BitmapStore& store, DataHandler<WorldData>& dataHandler);


	void update(float delta);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

