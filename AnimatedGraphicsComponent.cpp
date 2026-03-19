#include "AnimatedGraphicsComponent.h"
#include "AnimatedGraphicsAttributes.h"
#include "BitmapStore.h"
#include "GraphicsComponent.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "GameEngine.h"
#include "GraphicsAttributes.h"
#include <utility>
#include <memory>

void AnimatedGraphicsComponent::nextFrame()
{
	if (m_EndedAnimation)
	{
		return;
	}

	if (m_CurrentFrame >= m_Attributes.Animation.FrameCount)
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

AnimatedGraphicsComponent::AnimatedGraphicsComponent(BitmapStore& bitmapStore, GraphicsAttributes& attributes) :
	GraphicsComponent(bitmapStore, attributes.GraphicsId),
	m_Attributes(attributes)
{
}

void AnimatedGraphicsComponent::update(float delta)
{
	if (m_Attributes.Animation.Loop && m_EndedAnimation && GameEngine::GameTimeTotal.asSeconds() - m_TimeSinceLastAnimation >= m_Attributes.Animation.DelayBeforeAnimationStart)
	{
		m_EndedAnimation = false;

		m_CurrentFrame = 0;
	}

	if (!m_EndedAnimation && GameEngine::GameTimeTotal.asSeconds() - m_TimeSinceLastFrameUpdate >= m_Attributes.Animation.DelayBetweenFrames)
	{
		nextFrame();

		m_TimeSinceLastFrameUpdate = GameEngine::GameTimeTotal.asSeconds();
	}
}

void AnimatedGraphicsComponent::render(sf::RenderTarget& target)
{
	GraphicsComponent::render(target);
}