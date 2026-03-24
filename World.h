#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Tilemap.h"
#include "BitmapStore.h"
#include "WorldData.h"
#include "ProjectilesFactory.h"
#include "DataHandler.h"
#include "GraphicsAttributes.h"
#include "PolygonShapeAttributes.h"

class IGameObject;

using GameObjects = std::vector<std::unique_ptr<IGameObject>>;

class World : public sf::Drawable
{
private:
	GameObjects m_Entities;

	std::unique_ptr<Tilemap>   m_Tilemap;

	std::shared_ptr<WorldData> m_WorldData;
	std::shared_ptr<ProjectilesFactory> m_ProjectileFactory;

public:
	World(
		BitmapStore& store, 
		std::shared_ptr<WorldData> data, 
		std::shared_ptr<ProjectilesFactory> projectileFactory,
		std::shared_ptr<DataHandler<GraphicsAttributes>> graphicsDataHandler,
		std::shared_ptr<DataHandler<PolygonShapeAttributes>> shapeDataHandler
	);

	void update(float delta);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

