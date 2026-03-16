#pragma once
#include "GraphicsComponent.h"
#include "AnimatedGraphicsAttributes.h"
#include <SFML/System/Time.hpp>
#include "BitmapStore.h"
#include <SFML/Graphics/RenderTarget.hpp>

class AnimatedGraphicsComponent : public GraphicsComponent
{
private:
	AnimatedGraphicsAttributes m_Attributes;

	int m_CurrentFrame	   = 0;
	int m_CurrentAnimation = 0;

	float m_TimeSinceLastAnimation   = 0;
	float m_TimeSinceLastFrameUpdate = 0;

	bool m_EndedAnimation = false;

	void nextFrame();

public:
	AnimatedGraphicsComponent(BitmapStore& bitmapStore, AnimatedGraphicsAttributes attributes);	
	AnimatedGraphicsComponent(BitmapStore& bitmapStore) : GraphicsComponent(bitmapStore) {};

	void init(AnimatedGraphicsAttributes attributes);

	void update(float delta) override;
	void render(sf::RenderTarget& target) override;
};

