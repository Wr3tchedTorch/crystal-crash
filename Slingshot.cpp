#include "Slingshot.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include "BitmapStore.h"

const std::string Slingshot::BaseGraphicsId  = "Lamp Post 1 TALL - Silver.png";
const std::string Slingshot::ChainGraphicsId = "Chain - Bronze.png";

Slingshot::Slingshot(BitmapStore& store, sf::Vector2f position) :
	m_BaseGraphicsComponent(store, BaseGraphicsId),
	m_ChainGraphicsComponent(store, ChainGraphicsId)
{
	m_BaseGraphicsComponent.setPosition(position);
	m_ChainGraphicsComponent.setPosition({ 600, 200 });
}

void Slingshot::update(float delta)
{	
}

void Slingshot::render(sf::RenderTarget& target)
{
	m_BaseGraphicsComponent.render(target);
	m_ChainGraphicsComponent.render(target);
}
