#pragma once
#include "Tilemap.h"
#include <memory>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "BitmapStore.h"
#include "WorldData.h"
#include "DataHandler.h"
#include <vector>

class IGameObject;

using GameObjects = std::vector<std::unique_ptr<IGameObject>>;

class World : public sf::Drawable
{
private:
	GameObjects m_Entities;

	std::unique_ptr<Tilemap>   m_Tilemap;

	std::shared_ptr<WorldData> m_WorldData;

public:
	World(int levelToLoad, BitmapStore& store, DataHandler<WorldData>& dataHandler);

	void update(float delta);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

