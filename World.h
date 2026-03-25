#pragma once

#include <id.h>

#include <memory>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Tilemap.h"
#include "BitmapStore.h"
#include "WorldData.h"
#include "ProjectilesFactory.h"
#include "DataHandlerManager.h"
#include "Slingshot.h"

class IGameObject;

using GameObjects = std::vector<std::unique_ptr<IGameObject>>;

class World : public sf::Drawable
{
private:
	GameObjects m_Entities;

	std::unique_ptr<Tilemap>   m_Tilemap;

	std::shared_ptr<WorldData> m_WorldData;
	std::shared_ptr<ProjectilesFactory> m_ProjectileFactory;

	void initializeProjectiles(DataHandlerManager& handlerManager);
	void reloadSlingshot(std::vector<std::shared_ptr<ProjectileAttributes>> projectileAttributes, Slingshot& slingshot, std::shared_ptr<ProjectilesFactory> projectileFactory);

public:
	World(
		BitmapStore& store, 
		std::shared_ptr<WorldData> data, 
		std::shared_ptr<ProjectilesFactory> projectileFactory,
		DataHandlerManager& handlerManager,
		b2WorldId worldId
	);

	void update(float delta);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

