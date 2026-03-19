#include "StateSlingshotLoading.h"
#include <memory>
#include "ISlingshotState.h"
#include "Slingshot.h"
#include <SFML/Graphics/Rect.hpp>
#include "SlingshotConstants.h"
#include "StateSlingshotIdle.h"
#include <SFML/System/Vector2.hpp>

void StateSlingshotLoading::enter(Slingshot& slingshot)
{
	if (slingshot.m_LoadedProjectiles.empty())
	{
		return;
	}

	slingshot.m_LoadedProjectiles.front()->disableBody();
	m_Direction = (slingshot.m_BeakPosition - slingshot.m_LoadedProjectiles.front()->getPosition()).normalized();
	m_BeakPosition = slingshot.m_BeakPosition;
}

void StateSlingshotLoading::exit(Slingshot& slingshot)
{
}

std::unique_ptr<ISlingshotState> StateSlingshotLoading::update(Slingshot& slingshot, float delta)
{
	if (!slingshot.m_LoadedProjectiles.empty() && playProjectileLoadingAnimation(slingshot, delta))
	{
		loadNextProjectile(slingshot);

		return std::make_unique<StateSlingshotIdle>();
	}

	return nullptr;
}

sf::FloatRect StateSlingshotLoading::createTrigger()
{
	sf::FloatRect trigger;
	
	sf::Vector2f triggerPosition(m_BeakPosition);
	triggerPosition.x -= SlingshotConstants::LoadingAnimationDistanceTolerance;
	triggerPosition.y -= SlingshotConstants::LoadingAnimationDistanceTolerance;

	trigger.position = triggerPosition;
	trigger.size =
	{
		SlingshotConstants::LoadingAnimationDistanceTolerance * 2.0f,
		SlingshotConstants::LoadingAnimationDistanceTolerance * 2.0f
	};
	return trigger;
}

void StateSlingshotLoading::loadNextProjectile(Slingshot& slingshot)
{
	slingshot.m_LoadedProjectiles.front()->load();
	slingshot.m_LoadedProjectiles.front()->setRotation(sf::degrees(0));
}

bool StateSlingshotLoading::playProjectileLoadingAnimation(Slingshot& slingshot, float delta)
{
	slingshot.m_LoadedProjectiles.front()->getPosition() += m_Direction * SlingshotConstants::LoadingAnimationSpeed * delta;	

	sf::FloatRect trigger = createTrigger();

	return trigger.contains(slingshot.m_LoadedProjectiles.front()->getPosition());
}
