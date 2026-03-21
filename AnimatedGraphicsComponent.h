#pragma once
#include "GraphicsComponent.h"
#include "BitmapStore.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "GraphicsAttributes.h"
#include <memory>

class AnimatedGraphicsComponent : public GraphicsComponent
{
private:
	const std::shared_ptr<GraphicsAttributes> m_Attributes;

	int m_CurrentFrame	   = 0;
	int m_CurrentAnimation = 0;

	float m_TimeSinceLastAnimation   = 0;
	float m_TimeSinceLastFrameUpdate = 0;

	bool m_EndedAnimation = false;

	void nextFrame();

public:
	AnimatedGraphicsComponent(BitmapStore& bitmapStore, const std::shared_ptr<GraphicsAttributes> attributes);

	void update(float delta) override;
	void render(sf::RenderTarget& target) override;
};

