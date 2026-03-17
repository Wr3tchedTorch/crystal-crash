#include "AnimatedGraphicsComponent.h"
#include "AnimatedGraphicsAttributes.h"
#include "BitmapStore.h"
#include "GraphicsComponent.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "GameEngine.h"

void AnimatedGraphicsComponent::nextFrame()
{
	if (m_EndedAnimation)
	{
		return;
	}

	if (m_CurrentFrame >= m_Attributes.FrameCount)
	{
		m_EndedAnimation = true;
		return;
	}

	m_TimeSinceLastAnimation = GameEngine::GameTimeTotal.asSeconds();

	sf::IntRect toRect;
	toRect.position =
	{
		m_Attributes.TextureRect.size.x * m_CurrentFrame,
		m_Attributes.TextureRect.size.y * m_CurrentAnimation
	};
	toRect.size =
	{
		m_Attributes.TextureRect.size.x,
		m_Attributes.TextureRect.size.y
	};

	m_Sprite.setTextureRect(toRect);

	m_CurrentFrame++;	
}

AnimatedGraphicsComponent::AnimatedGraphicsComponent(BitmapStore& bitmapStore, AnimatedGraphicsAttributes attributes) :
	GraphicsComponent(bitmapStore),
	m_Attributes(attributes)
{
}

void AnimatedGraphicsComponent::init(AnimatedGraphicsAttributes attributes)
{
	m_Attributes = attributes;	
}

void AnimatedGraphicsComponent::update(float delta)
{
	if (m_Attributes.Loop && m_EndedAnimation && GameEngine::GameTimeTotal.asSeconds() - m_TimeSinceLastAnimation >= m_Attributes.DelayBeforeAnimationStart)
	{
		m_EndedAnimation = false;

		m_CurrentFrame = 0;
	}

	if (!m_EndedAnimation && GameEngine::GameTimeTotal.asSeconds() - m_TimeSinceLastFrameUpdate >= m_Attributes.DelayBetweenFrames)
	{
		nextFrame();

		m_TimeSinceLastFrameUpdate = GameEngine::GameTimeTotal.asSeconds();
	}
}

void AnimatedGraphicsComponent::render(sf::RenderTarget& target)
{
	GraphicsComponent::render(target);
}